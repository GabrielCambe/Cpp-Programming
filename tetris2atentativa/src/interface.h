#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>

/*
  2 columns per cell makes the game much nicer.
 */
#define COLS_PER_CELL 2
/*
  Macro to print a cell of a specific type to a window.
 */
#define ADD_BLOCK(w,x) waddch((w),' '|A_REVERSE|COLOR_PAIR(x));     \
                       waddch((w),' '|A_REVERSE|COLOR_PAIR(x))
#define ADD_EMPTY(w) waddch((w), ' '); waddch((w), ' ')

class Interface {
    public:
        WINDOW *board, *next, *hold, *score;

        void display_game();
        void doupdate();

        Interface(int rows, int cols){
            // NCURSES initialization:
            initscr();             // initialize curses
            cbreak();              // pass key presses to program, but not signals
            noecho();              // don't echo key presses to screen
            keypad(stdscr, TRUE);  // allow arrow keys
            timeout(0);            // no blocking on getch()
            curs_set(0);           // set the cursor to invisible
            init_colors();         // setup tetris colors

            // Create windows for each section of the interface.
            this->board = newwin(rows + 2, 2 * cols + 2, 0, 0);
            this->next  = newwin(6, 10, 0, 2 * (cols + 1) + 1);
            this->hold  = newwin(6, 10, 7, 2 * (cols + 1) + 1);
            this->score = newwin(6, 10, 14, 2 * (cols + 1 ) + 1);
        }
        ~Interface(){
            // Deinitialize NCurses
            wclear(stdscr);
            endwin();
        }
}