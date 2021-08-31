BUILD_DIR   = build
LATEX       = xelatex
LATEX_FLAGS = -shell-escape -output-directory $(BUILD_DIR)

all: build content
	$(LATEX) $(LATEX_FLAGS) main.tex && $(LATEX) $(LATEX_FLAGS) main.tex
	mv $(BUILD_DIR)/main.pdf .

clean:
	rm -rf $(BUILD_DIR) _minted-main

build:
	mkdir -p $(BUILD_DIR)

content:
	python3 content-generator.py config.yaml $(BUILD_DIR)/content.tex
