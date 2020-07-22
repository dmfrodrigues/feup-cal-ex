LATEXMK=latexmk -f -interaction=nonstopmode --shell-escape -pdf -quiet -silent

all: exams/CAL_exams.pdf

OUTFILES_EXTRA = $(shell find . -name "CAL_*.tex" | sed 's/.tex/.pdf/g')

extra: $(OUTFILES_EXTRA)

%.pdf: %.tex
ifeq ($(VERSION),)
	cd $(<D) && $(LATEXMK) $(<F)
else
	cd $(<D) && (echo "$(VERSION)" > VERSION) && $(LATEXMK) $(<F) && $(RM) VERSION
endif

clean:
	git clean -dfX
