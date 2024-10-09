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

TARGETS = array_basics caesar_cipher_demo game_entry.o scoreboard.o scoreboard_smart.o scoreboard_demo tic_tac_toe_demo vector_iterator_demo

#-----------------------------------------------------------------------
# Compilation
#-----------------------------------------------------------------------

default: $(TARGETS)

array_basics: array_basics.cpp
	$(BUILD) array_basics.cpp -o array_basics

caesar_cipher_demo: caesar_cipher_demo.cpp caesar_cipher.h
	$(BUILD) caesar_cipher_demo.cpp -o caesar_cipher_demo

game_entry.o: game_entry.cpp game_entry.h
	$(BUILD) -c game_entry.cpp

scoreboard.o: scoreboard.cpp scoreboard.h game_entry.h
	$(BUILD) -c scoreboard.cpp

scoreboard_smart.o: scoreboard_smart.cpp scoreboard_smart.h game_entry.h
	$(BUILD) -c scoreboard_smart.cpp

scoreboard_demo: scoreboard_demo.cpp scoreboard.o game_entry.o
	$(BUILD) scoreboard_demo.cpp scoreboard.o game_entry.o -o scoreboard_demo

tic_tac_toe_demo: tic_tac_toe_demo.cpp tic_tac_toe.h
	$(BUILD) tic_tac_toe_demo.cpp -o tic_tac_toe_demo

vector_iterator_demo: vector_iterator_demo.cpp vector.h
	$(BUILD20) vector_iterator_demo.cpp -o vector_iterator_demo


#-----------------------------------------------------------------------

clean:
	-rm -f *.o core *~ *.~* *.obj

realclean: clean
	-rm -f $(TARGETS)
	-rm -f *.exe
