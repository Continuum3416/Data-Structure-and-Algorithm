#include <string>

using namespace std;

namespace dsac::primer {

int count(string s, char target) {
    int total{0};
    for (char c : s)
        if (c == target)
            total++;
    return total;
}

int count(const char* s, int n, char target) {
    int total{0};
    for (int j=0; j < n; j++)
        if (s[j] == target)
            total++;
    return total;
}
    
void remove_all(string& s, char target) {
    int kept{0};                     // count of characters kept thus far
    for (int j=0; j < s.size(); j++)
        if (s[j] != target)          // keep s[j] in first "available" location
            s[kept++] = s[j];

    // shrink string by removing all characters from s[kept] to the end
    s.erase(kept, s.size()-kept);
}

    
}  // namespace dsac::primer


