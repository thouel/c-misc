#include <conio.h>
#include <pthread.h>
#include <unistd.h>

#include "chrono.h"

int main(int argc, char* argv[]) {
  COORD chronoPosition = {DISPLAY_ORG_CHRONO_BEGIN_X,
                          DISPLAY_ORG_CHRONO_BEGIN_Y};
  COORD menuPosition = {DISPLAY_ORG_MENU_BEGIN_X, DISPLAY_ORG_MENU_BEGIN_Y};
  status_t st;
  st = (status_t){.isRunning = 0, .hours = 0, .minutes = 0, .seconds = 0};
  pthread_t start_pt;

  clear_screen(chronoPosition);

  display_chrono(st.hours, st.minutes, st.seconds, chronoPosition);
  display_menu(&st, menuPosition);

  fflush(stdin);
  while (1) {
    if (_kbhit()) {
      char c = _getch();

      if ((st.isRunning == 0 || st.isRunning == 2) && (c == 'a' || c == 'A')) {
        // Start the stopwatch
        start_chrono_parameters_t scp = {.s = &st,
                                         .chronoPosition = chronoPosition};
        st.isRunning = 1;
        int t = pthread_create(&start_pt, NULL, start_chrono, &scp);
        if (t) {
          printf("Cannot build thread, exiting...");
          return t;
        }

        display_menu(&st, menuPosition);

      } else if (st.isRunning == 1 && (c == 'o' || c == 'O')) {
        // Stop the stopwatch
        st.isRunning = 2;
        int t = pthread_join(start_pt, NULL);
        if (t) {
          printf("Abnormal behaviour during thread stop");
          return EXIT_FAILURE;
        }

        display_menu(&st, menuPosition);

      } else if (st.isRunning == 2 && (c == 'e' || c == 'E')) {
        // Reset the stopwatch
        st.isRunning = 0;
        st.hours = 0;
        st.minutes = 0;
        st.seconds = 0;

        clear_screen(chronoPosition);
        display_chrono(st.hours, st.minutes, st.seconds, chronoPosition);
        display_menu(&st, menuPosition);
      } else if (c == 'q' || c == 'Q') {
        if (start_pt) {
          // No need to check the pthread_cancel
          pthread_cancel(start_pt);
        }
        return EXIT_SUCCESS;
      }
    }
  }

  return EXIT_SUCCESS;
}