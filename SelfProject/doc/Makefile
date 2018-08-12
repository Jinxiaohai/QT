EXE=learnQt.pdf
SRC=learnQt.tex
BIB=learnQt.aux

$(EXE):$(SRC)
	xelatex $(SRC)

.PHONY.:look
look:
	evince learnQt.pdf

.PHONY.:clean
clean:
	$(RM) learnQt.aux learnQt.log learnQt.dvi learnQt.bbl learnQt.blg learnQt.toc learnQt.out learnQt.nav learnQt.snm learnQt.thm learnQt.lot learnQt.lof
