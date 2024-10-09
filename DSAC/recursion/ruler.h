#pragma once

#include <iostream>
#include <string>

namespace dsac::recursion {

/// Draws a line with the given tick length, followed by an optional label.
void draw_line(int tickLength, int tickLabel = -1) {
    std::cout << std::string(tickLength, '-');
    if (tickLabel >= 0) std::cout << " " << tickLabel;
    std::cout << std::endl;
}

/// Draws a ruler interval around a central tick length.
void draw_interval(int centralLength) {
    if (centralLength >= 1) {               // otherwise, do nothing
        draw_interval(centralLength - 1);   // recursively draw top interval
        draw_line(centralLength);           // draw center tick line (without label)
        draw_interval(centralLength - 1);   // recursively draw bottom interval
    }
}

/// Draws an English ruler.
/// The level of division depends upon the designated length of the major tick.
/// For example, a major tick of length 3 will produce a ruler with ticks (of length 2)
/// at the half-inch mark and ticks (of length 1) at the quarter-inch marks.
///
/// @param nInches the total number of inches to be drawn
/// @param majorLength the number of dashes used at complete inch marks
void draw_ruler(int nInches, int majorLength) {
    draw_line(majorLength, 0);              // draw inch 0 line and label
    for (int j = 1; j <= nInches; j++) {
        draw_interval(majorLength - 1);     // draw interior ticks for inch
        draw_line(majorLength, j);          // draw inch j line and label
    }
}

}  // namespace dsac::recursion
