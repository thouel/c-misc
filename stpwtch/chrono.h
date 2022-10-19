#include "status.h"
#include "terminal.h"

#ifndef NUMBER_WIDTH
#define NUMBER_WIDTH 3
#define NUMBER_HEIGHT 3
#define DOUBLEPOINT_WIDTH 1
#endif

#ifndef DISPLAY_ORG_CHRONO_BEGIN_X
#define DISPLAY_ORG_CHRONO_BEGIN_X 0
#define DISPLAY_ORG_CHRONO_BEGIN_Y 10
#define DISPLAY_ORG_MENU_BEGIN_X 5
#define DISPLAY_ORG_MENU_BEGIN_Y 14
#endif

/**
 * Display organization
 * <chrono> => 0,0 up to 20,3
 * <space> => 0,4 up to 20,6
 * <menu> => 5,7 up to 15,7
 */
void display_number_part_top(int n);
void display_number_part_mid(int n);
void display_number_part_bot(int n);
void display_number(int n, COORD topLeft);
void display_doublepoint(COORD topLeft);

void display_chrono(int hrs, int min, int sec, COORD topLeft);
void display_chrono_part(int part, COORD topLeft);

void display_menu(status_t* status, COORD cursorPosition);

typedef struct {
  status_t* s;
  COORD chronoPosition;
} start_chrono_parameters_t;

void* start_chrono(void* scp);