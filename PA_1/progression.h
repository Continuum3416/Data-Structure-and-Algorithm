#pragma once
#include <iostream>

namespace dsac::design {

/// A base class generating a progression of numbers
class Progression {
protected:
    long current;

    /// Advances the current value to the next value of the progression
    virtual void advance() {
        current++;
    }
    
public:
    /// Constructs a progression with given start value (default: 0)
    Progression(long start = 0) : current{start} {}

    /// Destructs the progression
    virtual ~Progression() {};           // virtual destructor
    
    /// Returns the next value of the progression
    long next_value() {
        long answer{current};
        advance();              // this protected call is responsible for advancing the current value
        return answer;
    }

    /// Prints the next n values of the progression, separate by spaces
    void print_progression(int n) {
        std::cout << next_value();              // print the first value without leading space
        for (int j = 1; j < n; j++)
            std::cout << " " << next_value();   // print leading space before others
        std::cout << std::endl;
    }
    

};

}  
