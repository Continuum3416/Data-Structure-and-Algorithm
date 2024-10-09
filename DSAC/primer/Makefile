#-----------------------------------------------------------------------
#  This simple Makefile which compiles the various test programs
#  contained in this directory.
#
# Targets:
#
#       make			(default) Compile and run all test programs
#       make realclean          Remove all executable files
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Common definitions
#-----------------------------------------------------------------------------
include ../Make-config

#-----------------------------------------------------------------------------
# Targets
#-----------------------------------------------------------------------------

TARGETS = sum sample_functions.o count_function_demo remove_all_function_demo sample_functions_demo

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

sum: sum.cpp
	$(C++) $(CFLAGS) sum.cpp -o sum

sample_functions.o: sample_functions.cpp sample_functions.h
	$(C++) $(CFLAGS) -c sample_functions.cpp

count_function_demo: count_function_demo.cpp sample_functions.o
	$(C++) $(CFLAGS) count_function_demo.cpp sample_functions.o -o count_function_demo

remove_all_function_demo: remove_all_function_demo.cpp sample_functions.o
	$(C++) $(CFLAGS) remove_all_function_demo.cpp sample_functions.o -o remove_all_function_demo

sample_functions_demo: sample_functions.o sample_functions_demo.cpp
	$(C++) $(CFLAGS) sample_functions.o sample_functions_demo.cpp -o sample_functions_demo


#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
#	-rm -r *.exe
#	cd Test; make realclean
