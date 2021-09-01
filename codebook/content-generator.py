#!/usr/bin/env python3

import hashlib
import os
import re
import sys
import yaml
from pathlib import Path
import pygments.lexers
from queue import SimpleQueue


class DependencyGraph:

    def __init__(self, sources):
        self.sources = list(sources)
        self.id_map = {name: id_ for id_, name in enumerate(sources)}
        self.use_sets = [set() for _ in sources]
        self.dep_sets = [set() for _ in sources]

    def add_dependency(self, source1, source2):
        """source1 depends on source2"""
        try:
            id1, id2 = self.id_map[source1], self.id_map[source2]
        except KeyError as e:
            raise KeyError(f'`{e}` is not a valid source file.')
        self.use_sets[id2].add(id1)
        self.dep_sets[id1].add(id2)

    def get_dependencies(self, source):
        try:
            id_ = self.id_map[source]
        except KeyError as e:
            raise KeyError(f'`{e}` is not a valid source file.')
        for dep in self.dep_sets[id_]:
            yield self.sources[dep]

    def topological_sort(self):
        """returns a topological sorting for the sources, or None if there
        is a dependency cycle."""
        result = []
        in_degrees = [len(dep_set) for dep_set in self.dep_sets]
        queue = SimpleQueue()
        print(self.use_sets, in_degrees)
        for node, deg in enumerate(in_degrees):
            if deg == 0:
                queue.put(node)
        while not queue.empty():
            cur = queue.get()
            result.append(self.sources[cur])
            for dep in self.use_sets[cur]:
                if dep == cur:
                    return None
                in_degrees[dep] -= 1
                if in_degrees[dep] == 0:
                    queue.put(dep)
        return result if len(result) == len(self.sources) else None


def get_includes(filename):
    INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"(.+?)"')
    with open(filename, 'r') as file:
        for line in file:
            match = INCLUDE_RE.match(line)
            if match:
                include_path = Path(filename).parent / Path(match.group(1))
                include_path = include_path.resolve()
                if not include_path.is_file():
                    raise FileNotFoundError(f'Non-existent include file '
                                            f'`{include_path}` in {filename}')
                yield str(include_path)


def generate_content(config):
    dependency_config = config.get('dependencies', dict())
    show_dependencies = dependency_config.get('show', True)
    ignore_dep_cycles = dependency_config.get('ignore_cycles', False)

    file_info_map = dict()  # filename -> (title, language)

    LATEX_DEPTHS = ['section', 'subsection', 'subsubsection',
                    'paragraph', 'subparagraph']

    def parse_all(sections, title):
        for section in sections:
            if isinstance(section, dict):
                for subtitle, subsections in section.items():
                    parse_all(subsections, subtitle)
            elif isinstance(section, str):
                path = str((Path('../nacl') / Path(section)).resolve())
                lexer = pygments.lexers.find_lexer_class_for_filename(path)
                lang = lexer.aliases[0]
                if path in file_info_map:
                    raise KeyError(f'Duplicate source file `{path}`.')
                file_info_map[path] = (title, lang)

    includes = config.get('include')
    if not includes:
        raise KeyError('Key `include` not found in config.')

    parse_all(includes, 'include')
    print(file_info_map)

    dependency_graph = DependencyGraph(file_info_map.keys())
    for filename, (title, lang) in file_info_map.items():
        if lang == 'cpp' or lang == 'c':
            for dependency in get_includes(filename):
                dependency_graph.add_dependency(filename, dependency)

    if not ignore_dep_cycles and not dependency_graph.topological_sort():
        raise ValueError('Dependency cycle detected. Change dependencies.'
                         'ignore_cycles to true to supress this error.')

    def generate_content_internal(sections, title, depth):
        if depth >= 0:
            yield f'\\{LATEX_DEPTHS[depth]}{{{title}}}'
        for section in sections:
            if isinstance(section, dict):
                for subtitle, subsections in section.items():
                    yield from generate_content_internal(
                        subsections, subtitle, depth + 1)
            elif isinstance(section, str):
                path = str((Path('../nacl') / Path(section)).resolve())
                title, lang = file_info_map[path]
                if lang == 'tex':
                    yield f'\\input{{{path}}}'
                    continue
                dep_str = ', '.join(file_info_map[dep][0] for dep in
                                    dependency_graph.get_dependencies(path))
                if show_dependencies and dep_str:
                    yield f'\\requires{{{dep_str}}}'
                hash_ = hashlib.sha256(open(path, 'rb').read()).hexdigest()[:16]
                yield f'\\inputcode{{{lang}}}{{{path}}}{{build/{hash_}}}'

    yield from generate_content_internal(includes, 'include', -1)


def main():
    if len(sys.argv) != 3:
        print(f'Usage: {sys.argv[0]} <config_file> <output_file>')
        exit(1)

    _, infile, outfile = sys.argv

    with open(infile, 'r') as file:
        config = yaml.safe_load(file)

    with open(outfile, 'w') as file:
        for line in generate_content(config):
            file.write(line + '\n')


if __name__ == '__main__':
    main()
