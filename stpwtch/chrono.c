#include "chrono.h"

void display_number_part_top(int n) {
  if (n == 0 || n == 2 || n == 3 || n == 5 || n == 6 || n == 7 || n == 8 ||
      n == 9) {
    printf(" _");
  }
}

void display_number_part_mid(int n) {
  if (n == 0) {
    printf("| |");
  }
  if (n == 1) {
    printf("  |");
  }
  if (n == 2) {
    printf(" _|");
  }
  if (n == 3) {
    printf(" _|");
  }
  if (n == 4) {
    printf("|_|");
  }
  if (n == 5) {
    printf("|_ ");
  }
  if (n == 6) {
    printf("|_ ");
  }
  if (n == 7) {
    printf("  |");
  }
  if (n == 8) {
    printf("|_|");
  }
  if (n == 9) {
    printf("|_|");
  }
}

void display_number_part_bot(int n) {
  if (n == 0) {
    printf("|_|");
  }
  if (n == 1) {
    printf("  |");
  }
  if (n == 2) {
    printf("|_ ");
  }
  if (n == 3) {
    printf(" _|");
  }
  if (n == 4) {
    printf("  |");
  }
  if (n == 5) {
    printf(" _|");
  }
  if (n == 6) {
    printf("|_|");
  }
  if (n == 7) {
    printf("  |");
  }
  if (n == 8) {
    printf("|_|");
  }
  if (n == 9) {
    printf(" _|");
  }
}

void display_number(int n, COORD topLeft) {
  COORD midLeft = {topLeft.X, topLeft.Y + 1};
  COORD botLeft = {topLeft.X, topLeft.Y + 2};

  goto_position(topLeft);
  display_number_part_top(n);
  goto_position(midLeft);
  display_number_part_mid(n);
  goto_position(botLeft);
  display_number_part_bot(n);
}

void display_doublepoint(COORD topLeft) {
  COORD midLeft = {topLeft.X, topLeft.Y + 1};
  COORD botLeft = {topLeft.X, topLeft.Y + 2};

  // skip topLeft, nothing to write on first line
  goto_position(midLeft);
  printf(".");
  goto_position(botLeft);
  printf(".");
}

void display_chrono_part(int part, COORD topLeft) {
  display_number(part / 10, topLeft);
  topLeft.X += NUMBER_WIDTH;
  display_number(part % 10, topLeft);
}

void display_chrono(int hrs, int min, int sec, COORD topLeft) {
  if (hrs < 0 || hrs > 99) {
    fprintf(stderr, "Hours < 0 or > 99");
    return;
  }
  if (min < 0 || min > 59) {
    fprintf(stderr, "Min < 0 or > 59");
    return;
  }
  if (sec < 0 || sec > 59) {
    fprintf(stderr, "Sec < 0 or > 59");
    return;
  }

  COORD currentCoord = topLeft;

  // Display the hours part "00", "01", "02", ...
  display_chrono_part(hrs, currentCoord);

  // Set the next character's topleft coordinate
  currentCoord.X += NUMBER_WIDTH * 2;

  // Display the double point ':'
  display_doublepoint(currentCoord);

  // Set the next character's topleft coordinate
  currentCoord.X += DOUBLEPOINT_WIDTH;

  display_chrono_part(min, currentCoord);

  currentCoord.X += NUMBER_WIDTH * 2;

  display_doublepoint(currentCoord);

  currentCoord.X += DOUBLEPOINT_WIDTH;

  display_chrono_part(sec, currentCoord);
}

void display_menu(status_t* status, COORD cursorPosition) {
  goto_position(cursorPosition);

  // printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*");
  // printf("       Stopwatch by justobit         ");
  // printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*");
  if (status->isRunning == 0) {
    printf("St[a]rt");
  } else if (status->isRunning == 1) {
    printf("St[o]p");
  } else if (status->isRunning == 2) {
    printf("St[a]rt - R[e]set");
  }
}

void* start_chrono(void* /*start_chrono_parameters_t*/ param) {
  start_chrono_parameters_t* scp = param;
  while (scp->s->isRunning == 1) {
    clear_chrono_line(scp->chronoPosition);

    if (scp->s->seconds && !(scp->s->seconds % 60))
      scp->s->seconds = 0, scp->s->minutes++;
    if (scp->s->minutes && !(scp->s->minutes % 60))
      scp->s->minutes = 0, scp->s->hours++;
    if (scp->s->hours && !(scp->s->hours % 100))
      scp->s->hours = 0, scp->s->minutes = 0, scp->s->seconds = 0;

    display_chrono(scp->s->hours, scp->s->minutes, scp->s->seconds,
                   scp->chronoPosition);
    Sleep(1000);
    scp->s->seconds++;
  }

  return NULL;
}