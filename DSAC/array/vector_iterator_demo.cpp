#include <cstdlib>  // provides EXIT_SUCCESS
#include <iostream>
#include <string>

#include "array/vector.h"

using namespace std;
using namespace dsac::array;

void display(const Vector<string>& vec, const string& label) {
    cout << label << "(length " << vec.size() << "):";
    for (string s : vec) cout << " " << s;
    cout << endl;
}

int main() {

    Vector<string> trip;                // our class only has a default constructor

    for (string airport : { "GRU", "BOG", "SCL", "LIM", "BSB"})
        trip.insert(trip.end(), airport);
    
    display(trip,"Original");

    Vector<string>::iterator walk{trip.begin()};
    while (walk != trip.end()) {
        if (walk->starts_with('B'))
            walk = trip.erase(walk);    // udpate walk to what comes after the erase
        else
            ++walk;                     // advance walk to the next location
    }
    
    display(trip,"Final");
    return EXIT_SUCCESS;
}
