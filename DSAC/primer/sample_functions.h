#pragma once

#include <string>

namespace dsac::primer {

/// Returns the number of occurrences of target character in string s
int count(std::string s, char target);

/// Returns the number of occurrences of target character in the n-character array s
int count(const char* s, int n, char target);

/// Removes all occurrences of target character from string s
void remove_all(std::string& s, char target);
    
} // namespace
