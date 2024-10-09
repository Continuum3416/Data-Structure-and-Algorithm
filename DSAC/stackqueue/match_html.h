#pragma once
#include <stack>
#include <string>

namespace dsac::stackqueue {

/// Tests if every opening tag has a matching closing tag in HTML string.
/// @param html a string representing the html source
/// @return true if properly matched, false otherwise   
bool is_html_matched(const std::string& html) {
    std::stack<std::string> buffer;
    int j(html.find('<'));                             // find first '<' character (if any)
    while (j != std::string::npos) {
        size_t k{html.find('>', j+1)};                    // find next '>' character (if any)
        if (k == std::string::npos) return false;         // invalid tag
        std::string tag{html.substr(j+1, k-j-1)};         // strip away < >
        if (tag.substr(0,1) != "/")                       // this is an opening tag
            buffer.push(tag);
        else {
            if (buffer.empty())
                return false;                             // no tag to match
            if (tag.substr(1) != buffer.top())
                return false;                             // mismatched tag
            buffer.pop();                                 // remove matched tag
        }
        j = html.find('<', k+1);                          // find next '<' character (if any)
    }
    return buffer.empty();                                // were all opening delimiters matched?
}

}  // namespace dsac::stackqueue
