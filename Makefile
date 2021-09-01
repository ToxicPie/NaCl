CLANG_FORMAT = clang-format

help:
	@echo "Available commands:"
	@echo "    make help           - Show this help"
	@echo "    make codebook       - Build the codebook PDF"
	@echo "    make format         - Run clang-format on all source files"
	@echo "    make tests          - Compile all the tests"
	@echo "    make clean-latex    - Remove LaTeX build files"
	@echo "    make clean-tests    - Remove test files"
	@echo "    make clean          - Clean up all build processes"

codebook: format
	$(MAKE) -C codebook all
	mv codebook/main.pdf codebook.pdf

format:
	find nacl/ -type f -regex ".*\.\(c\|h\|cpp\|hpp\)" \
		-exec $(CLANG_FORMAT) -i {} +

tests:

clean-latex:
	$(MAKE) -C codebook clean
