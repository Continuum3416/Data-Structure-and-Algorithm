#-----------------------------------------------------------------------
#  This simple Makefile which compiles the various test programs
#  contained in this directory.
#
# Targets:
#
#       make			(default) Compile and run all test programs
#       make clean              Remove object files and backup files
#       make realclean          Remove all executable files
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Common definitions
#-----------------------------------------------------------------------------
include ../Make-config

#-----------------------------------------------------------------------------
# Targets
#-----------------------------------------------------------------------------

TARGETS = stack_usage test_match_html

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

stack_usage: stack_usage.cpp stack.h
	$(C++) $(CFLAGS) stack_usage.cpp -o stack_usage

test_match_html: test_match_html.cpp match_html.h
	$(C++) $(CFLAGS) test_match_html.cpp -o test_match_html

#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
#	-rm -r *.exe
#	cd Test; make realclean
