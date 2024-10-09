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

TARGETS = string_experiment find_max_demo disjoint_set_demo prefix_average_demo find_first_demo exercises_demo

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

string_experiment: string_experiment.cpp
	$(BUILD) string_experiment.cpp -o string_experiment

find_max_demo: find_max.h find_max_demo.cpp
	$(BUILD) find_max_demo.cpp -o find_max_demo

disjoint_set_demo: disjoint_set.h disjoint_set_demo.cpp
	$(BUILD) disjoint_set_demo.cpp -o disjoint_set_demo

prefix_average_demo: prefix_average.h prefix_average_demo.cpp
	$(BUILD) prefix_average_demo.cpp -o prefix_average_demo

find_first_demo: find_first.h find_first_demo.cpp
	$(BUILD) find_first_demo.cpp -o find_first_demo

exercises_demo: exercises.h exercises_demo.cpp
	$(BUILD) exercises_demo.cpp -o exercises_demo

#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
	-rm -f *.exe

