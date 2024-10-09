#include "design/counter.h"

namespace dsac::design {

Counter::Counter() {};

Counter::Counter(int initial) : value{initial} {}

int Counter::get_value() const { return value; }

void Counter::increment() { value++; }

void Counter::increment(int delta) { value += delta; }

void Counter::reset() { value = 0; }
    
}  // namespace dsac::design
