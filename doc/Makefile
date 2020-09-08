.PHONY: all clean distclean

all: ghostscript-on-ivm64.pdf

ghostscript-on-ivm64.pdf: ghostscript-on-ivm64.tex
	pdflatex ghostscript-on-ivm64.tex
	pdflatex ghostscript-on-ivm64.tex

clean:
	rm -f ghostscript-on-ivm64.aux ghostscript-on-ivm64.log

distclean: clean
	rm -f ghostscript-on-ivm64.pdf
