#pragma once
#include <stack>
#include <string>

namespace dsac::stackqueue {

/// Tests if delimiters in the given expression are properly matched.
/// @param expression a character string
/// @return true if properly matched, false otherwise   
bool is_matched(const std::string& expression) {
    const std::string opening("({[");
    const std::string closing(")}]");
    std::stack<char> buffer;
    for (char c : expression) {
        if (opening.find(c) != std::string::npos)         // this is a left delimiter
            buffer.push(c);
        else if (closing.find(c) != std::string::npos) {  // this is a right delimiter
            if (buffer.empty())
                return false;                             // nothing to match with
            if (buffer.top() != opening[closing.find(c)])
                return false;                             // mismatched delimiter
            buffer.pop();                                 // remove matched opener
        }
    }
    return buffer.empty();                                // were all opening delimiters matched?
}

}  // namespace dsac::stackqueue
