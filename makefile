LATEXMK=latexmk -f -interaction=nonstopmode --shell-escape -pdf

all: exams/CAL_exams.pdf

%.pdf: %.tex
	cd $(<D) && $(LATEXMK) $(<F)

cleanall:
	git clean -dfX
