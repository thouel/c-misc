#include "terminal.h"

void goto_position(COORD position) {
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void clear_chrono_line(COORD topLeft) {
  for (int y = topLeft.Y; y < topLeft.Y + CHRONO_LINE_HEIGHT; y++) {
    for (int x = topLeft.X; x < topLeft.X + CHRONO_LINE_WIDTH; x++) {
      printf(" ");
    }
    COORD c = {topLeft.X, y};
    goto_position(c);
  }
}

void clear_screen(COORD position) {
  goto_position(position);
  for (int y = position.Y; y < position.Y + TERMINAL_HEIGHT; y++) {
    for (int x = position.X; x < position.X + TERMINAL_WIDTH; x++) {
      printf(" ");
    }
    COORD c = {position.X, y};
    goto_position(c);
  }
}