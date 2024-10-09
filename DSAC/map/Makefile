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

TARGETS = word_count hash_code.o test_hash_code test_cost_performance

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

word_count: word_count.cpp abstract_map.h abstract_hash_map.h probe_hash_map.h
	$(C++) $(CFLAGS) word_count.cpp -o word_count

hash_code.o: hash_code.cpp hash_code.h
	$(C++) $(CFLAGS) hash_code.cpp -c

test_hash_code: hash_code.o test_hash_code.cpp
	$(C++) $(CFLAGS) test_hash_code.cpp hash_code.o -o test_hash_code

test_cost_performance: test_cost_performance.cpp ordered_table_map.h
	$(C++) $(CFLAGS) test_cost_performance.cpp -o test_cost_performance


#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
#	-rm -r *.exe
#	cd Test; make realclean
