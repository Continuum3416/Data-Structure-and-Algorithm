// Note:  This version relies on a call to file_size even on directories,
// but that functionality is not guaranteed across all platforms.
// If there are problems, the call could be restricted only to
// regular files (and if desired, the stat/stat.h library could provide
// lower-level support on some systems).

#include <cstdlib>     // provides EXIT_SUCCESS
#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::filesystem;

/// Calculates the total disk usage (in bytes) of the portion of the file system rooted
/// at the given entry, while printing a summary akin to the standard 'du' Unix tool.
/// @param a directory_entry denoting the relevant portion of the file system
/// @return total number of bytes used by the designated portion of the file system
long disk_usage(directory_entry entry) {
    long total{0};
    if (!entry.is_directory())                                   // for a regular file
        total += entry.file_size();                              // add the file's size
    else {                                                       // but if a directory,
        for (directory_entry child : directory_iterator(entry))  // then for each child
            total += disk_usage(child);                          // add child's (recursive) usage to total
        // the following line is system dependent...
        total += entry.file_size();                              // and space used by the directory
    }
    cout << total << "\t" << entry.path().string() << endl;      // descriptive output
    return total;                                                // return the grand total
}


int main(int argc, char* argv[]) {
    if (argc >= 2) {
        disk_usage(directory_entry(path(argv[1])));
    } else {
        cout << "Enter the starting location as a command-line argument" << endl;
    }        
    
    return EXIT_SUCCESS;
}

