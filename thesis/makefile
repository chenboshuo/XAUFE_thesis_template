.PHONY : all clean help main main.tex sections/tree.txt
.ONESHELL: # Applies to every targets in the file!
.INTERMEDIATE : inkscape tree
## make all : regenerate all results.
all: inkscape main ebook draft release open_report

## make main : genreate the main pdf
main: inkscape build/main.pdf

## make quick: quick mode, just xelatex once,it ignore the bib files
quick: inkscape main.tex build
	xelatex -output-directory="./build" main.tex

## make open_report : generate open report(开题报告)
open_report: build/open_report.pdf

## make *.pdf : generate the pdf files
build/%.pdf: %.tex build
	xelatex -output-directory="./build" $<
	bibtex ./build/$(basename $<)
	xelatex -output-directory="./build" $<
	xelatex -output-directory="./build" $<

## make inkscape: if has inkscape svg,convert it into pdf+latex version
inkscape:
	cd figures
	for i in $$(find . -type f -name '*.svg');do
		inkscape $$i --export-filename=_$$(basename $$i .svg ).pdf \
		  --export-latex --export-area-drawing
	done

clean:
	# git ls-files --others | xargs gio trash
	git clean -fXd

## make build: create directory build
build:
	mkdir build

ebook.tex : build
	echo "\documentclass[draft,ebook]{XaufeThesisTemplate}" > ebook.tex
	awk 'FNR>4' main.tex >> ebook.tex

draft.tex : build
	echo "\documentclass[draft]{XaufeThesisTemplate}" > draft.tex
	awk 'FNR>4' main.tex >> draft.tex

release.tex : build
	echo "\documentclass{XaufeThesisTemplate}" > release.tex
	awk 'FNR>4' main.tex >> release.tex

## make draft: make build/draft.pdf
draft: build/draft.pdf
	rm -f draft.tex

## make release: make build/release.pdf
release: build/release.pdf
	rm -f release.tex

## make ebook: make build/ebook.pdf
ebook: build/ebook.pdf
	rm -f ebook.tex

## make help : show this message.
help :
	@grep -h -E '^##' ${MAKEFILE_LIST} | sed -e 's/## //g' \
		| column -t -s ':'
