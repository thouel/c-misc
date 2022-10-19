#include <stdio.h>
#include <windows.h>

#ifndef TERMINAL_HEIGHT
#define TERMINAL_HEIGHT 10
#define TERMINAL_WIDTH 20
#define CHRONO_LINE_HEIGHT 3
#define CHRONO_LINE_WIDTH 20
#endif

void goto_position(COORD position);
void clear_chrono_line(COORD topLeft);
void clear_screen(COORD position);