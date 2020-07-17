LATEXMK=latexmk -f -interaction=nonstopmode --shell-escape -pdf

all: exams/CAL_exams.pdf

%.pdf: %.tex
ifeq ($(VERSION),)
	cd $(<D) && $(LATEXMK) $(<F)
else
	cd $(<D) && (echo "$(VERSION)" > VERSION) && $(LATEXMK) $(<F) && $(RM) VERSION
endif
