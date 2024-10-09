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

TARGETS = counter_demo counter.o credit_card_demo predatory_credit_card_demo test_progression

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

counter.o: counter.h counter.cpp
	$(C++) $(CFLAGS) -c counter.cpp

counter_demo: counter_demo.cpp counter.o
	$(C++) $(CFLAGS) counter_demo.cpp counter.o -o counter_demo

credit_card_demo: credit_card_demo.cpp credit_card.h
	$(C++) $(CFLAGS) credit_card_demo.cpp -o credit_card_demo

predatory_credit_card_demo: predatory_credit_card_demo.cpp predatory_credit_card.h credit_card.h
	$(C++) $(CFLAGS) predatory_credit_card_demo.cpp -o predatory_credit_card_demo

test_progression: test_progression.cpp progression.h arithmetic_progression.h geometric_progression.h fibonacci_progression.h
	$(C++) $(CFLAGS) test_progression.cpp -o test_progression


#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
	-rm -f *.exe
