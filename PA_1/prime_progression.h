#pragma once
#include <iostream>

namespace dsac::design {

class PrimeProgression : public Progression {
  protected:
    long prime_increment = 0;
    
    virtual bool isPrime(int n) {
        if (n <= 1)
            return false;
        for (int i = 2; i <= n/2; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    
    // Returns the next prime number greater than or equal to the given number
    virtual int findNextPrime(int number) {
        while (!isPrime(number)) {
            number++;
        }
        return number;
    }
    
    virtual void advance(){
        prime_increment = findNextPrime(++current); // same as current+1
        current = prime_increment;
    }
    
  public:
    PrimeProgression(long start = 2) : Progression{start} {
        if (!isPrime(start)) {
            start = findNextPrime(start); // Find the next prime if start isn't prime
        }
        current = start;
    }
    
    // PrimeProgression(long start = 2) {
    //     if (!isPrime(start)) {
    //         start = findNextPrime(start); // Find the next prime if start isn't prime
    //     }
    //     current = start;
    // }
    
    
}; // PrimeProgression class

}
