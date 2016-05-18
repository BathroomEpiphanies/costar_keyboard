MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------
MSG_CLEANING = Cleaning project:

# Default target.
all: begin doc end

begin:
	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
	@echo

doc: tutorial.html

STMD=../../stmd/stmd
DOC_SOURCES=../keyboard/main.c ../keyboard/hw_interface.c
DOC_MD=$(DOC_SOURCES:.c=.md)

tutorial.html: $(DOC_MD) _header.html _footer.html
	rm -f $@
	cat _header.html >> $@
	$(STMD) introduction.md >> $@
	for md in $(DOC_MD) ; do $(STMD) $$md >> $@ ; done
	cat _footer.html >> $@

.INTERMEDIATE: $(DOC_MD)
%.md: %.c
	./c-to-md.sh $< > $@

# Target: clean project.
clean: begin clean_list end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	rm -f tutorial.html

# Listing of phony targets.
.PHONY : all begin finish end doc
