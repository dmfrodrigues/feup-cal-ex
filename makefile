all: exams/CAL_exams.pdf

%.pdf: %.tex
	cd $(<D) && latexmk -f -interaction=nonstopmode -pdf $(<F)

cleanall:
	git clean -dfX
