# by Heredia, Eduardo (C) 2011

.PHONY: all clean

all: pi pi.pdf

aloca: aloca_desaloca.c
	gcc aloca_desaloca.c -o aloca_desaloca -Wall -std=c99

pi: pi.c
	gcc pi.c -o pi -Wall -std=c99

pi.pdf: pi.tex
	pdflatex pi.tex
	@rm -f pi.aux
	@rm -f pi.log

clean:
	@rm -f pi
	@rm -f pi.pdf
	@rm -f pi.aux
	@rm -f pi.log
