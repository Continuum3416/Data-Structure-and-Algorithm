#include <cstdlib>
#include <iostream>
using namespace std;

#include "progression.h"
#include "arithmetic_progression.h"
#include "geometric_progression.h"
#include "fibonacci_progression.h"
using namespace dsac::design;

int main() {
    /** Test program for the progression classes */
    Progression* prog;

    // test AritheticProgression
    cout << "Arithmetic progression with default increment: ";
    prog = new ArithmeticProgression();
    prog->print_progression(10);
    
    cout << "Arithmetic progression with increment 5: ";
    prog = new ArithmeticProgression(5);
    prog->print_progression(10);
    
    cout << "Arithmetic progression with increment 5 and start 2: ";
    prog = new ArithmeticProgression(5, 2);
    prog->print_progression(10);
    
    // test GeometricProgression
    cout << "Geometric progression with default base: ";
    prog = new GeometricProgression();
    prog->print_progression(10);
    
    cout << "Geometric progression with base 3: ";
    prog = new GeometricProgression(3);
    prog->print_progression(10);

    // test FibonacciProgression
    cout << "Fibonacci progression with default start values: ";
    prog = new FibonacciProgression();
    prog->print_progression(10);
    
    cout << "Fibonacci progression with start values 4 and 6: ";
    prog = new FibonacciProgression(4, 6);
    prog->print_progression(10);
    
    return EXIT_SUCCESS;                   // successful execution
}
