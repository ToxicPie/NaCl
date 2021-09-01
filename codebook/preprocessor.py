#!/usr/bin/env python3

import sys
import re


def process_code(filename):
    KEEP_LINE_MACRO = '// keep-line\n'
    INCLUDE_RE = re.compile(r'^\s*#\s*include.*$')
    CLANG_FORMAT_RE = re.compile(r'\s*(//|/\*) clang-format .*')
    C_COMMENT_RE = re.compile(r'\s*///.*$')
    PY_COMMENT_RE = re.compile(r'\s*###.*$')
    with open(filename, 'r') as file:
        for line in file:
            if line.strip() == '':
                yield '\n'
                continue
            if line.endswith(KEEP_LINE_MACRO):
                line = line.rstrip(KEEP_LINE_MACRO) + '\n'
            else:
                line = INCLUDE_RE.sub('', line)
                line = CLANG_FORMAT_RE.sub('', line)
                line = C_COMMENT_RE.sub('', line)
                line = PY_COMMENT_RE.sub('', line)
            if line:
                yield line


def main():
    if len(sys.argv) != 3:
        print(f'Usage: {sys.argv[0]} <input_file> <output_file>')
        exit(1)

    _, infile, outfile = sys.argv

    with open(outfile, 'w') as file:
        for line in process_code(infile):
            file.write(line)


if __name__ == '__main__':
    main()
