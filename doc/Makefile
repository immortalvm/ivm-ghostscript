.PHONY: all clean distclean

all: ghostscript-on-ivm64.pdf ghostscript-performance.pdf

ghostscript-on-ivm64.pdf: ghostscript-on-ivm64.tex
	pdflatex ghostscript-on-ivm64.tex
	pdflatex ghostscript-on-ivm64.tex


ghostscript-performance.pdf: ghostscript-performance.tex
	pdflatex ghostscript-performance.tex
	pdflatex ghostscript-performance.tex

clean:
	rm -f ghostscript-on-ivm64.aux ghostscript-on-ivm64.log
	rm -f ghostscript-performance.aux ghostscript-performance.log

distclean: clean
	rm -f ghostscript-on-ivm64.pdf
	rm -f ghostscript-performance.pdf
