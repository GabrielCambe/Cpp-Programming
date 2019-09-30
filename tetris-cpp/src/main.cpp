/*****************************************************************************

  @file         main.c

  @author       Stephen Brennan

  @date         Created Wednesday, 10 June 2015

  @brief        Main program for tetris.

  @copyright    Copyright (c) 2015, Stephen Brennan.  Released under the Revised
                BSD License.  See LICENSE.txt for details.

*******************************************************************************/

#include <iostream>
// #include <stdio.h>
#include <cstdbool>
// #include <stdbool.h>
#include <cstdlib>
// #include <stdlib.h>
#include <ctime>
// #include <time.h>
#include <ncurses.h>
#include <cstring>
// #include <string.h>

#include "tetris.h"
// #include "util.h"

// /*
//   2 columns per cell makes the game much nicer.
//  */
// #define COLS_PER_CELL 2
// /*
//   Macro to print a cell of a specific type to a window.
//  */
// #define ADD_BLOCK(w,x) waddch((w),' '|A_REVERSE|COLOR_PAIR(x));     \
//                        waddch((w),' '|A_REVERSE|COLOR_PAIR(x))
// #define ADD_EMPTY(w) waddch((w), ' '); waddch((w), ' ')



// class Interface{
//   public:
//     WINDOW *board, *next, *hold, *score;

//     /*
//       Print the tetris board onto the ncurses window.
//      */
//     void display_board(WINDOW *w, tetris_game *obj)
//     {
//       int i, j;
//       box(w, 0, 0);
//       for (i = 0; i < obj->rows; i++) {
//         wmove(w, 1 + i, 1);
//         for (j = 0; j < obj->cols; j++) {
//           if (TC_IS_FILLED(tg_get(obj, i, j))) {
//             ADD_BLOCK(w,tg_get(obj, i, j));
//           } else {
//             ADD_EMPTY(w);
//           }
//         }
//       }
//       wnoutrefresh(w);
//     }

//     /*
//       Display a tetris piece in a dedicated window.
//     */
//     void display_piece(WINDOW *w, tetris_block block)
//     {
//       int b;
//       tetris_location c;
//       wclear(w);
//       box(w, 0, 0);
//       if (block.typ == -1) {
//         wnoutrefresh(w);
//         return;
//       }
//       for (b = 0; b < TETRIS; b++) {
//         c = TETROMINOS[block.typ][block.ori][b];
//         wmove(w, c.row + 1, c.col * COLS_PER_CELL + 1);
//         ADD_BLOCK(w, TYPE_TO_CELL(block.typ));
//       }
//       wnoutrefresh(w);
//     }

//     /*
//       Display score information in a dedicated window.
//      */
//     void display_score(WINDOW *w, tetris_game *tg)
//     {
//       wclear(w);
//       box(w, 0, 0);
//       wprintw(w, "Score\n%d\n", tg->points);
//       wprintw(w, "Level\n%d\n", tg->level);
//       wprintw(w, "Lines\n%d\n", tg->lines_remaining);
//       wnoutrefresh(w);
//     }


//     void display_update( tetris_game *tg ){
//       display_board(this->board, tg);
//       display_piece(this->next, tg->next);
//       display_piece(this->hold, tg->stored);
//       display_score(this->score, tg);
//       doupdate();
//       sleep_milli(10);
//     }

//     Interface( tetris_game *tg ){
//       // Create windows for each section of the interface.
//       this->board = newwin(tg->rows + 2, 2 * tg->cols + 2, 0, 0);
//       this->next  = newwin(6, 10, 0, 2 * (tg->cols + 1) + 1);
//       this->hold  = newwin(6, 10, 7, 2 * (tg->cols + 1) + 1);
//       this->score = newwin(6, 10, 14, 2 * (tg->cols + 1 ) + 1);
//     }
// };


// class Game{
//   public:
//     tetris_game *tg;
//     tetris_move move = TM_NONE;
//     Interface interface = Interface( this->tg );

//   void get_command( bool *running ){
//     switch (getch()) {
//     case KEY_LEFT:
//       this->move = TM_LEFT;
//       break;
//     case KEY_RIGHT:
//       this->move = TM_RIGHT;
//       break;
//     case KEY_UP:
//       this->move = TM_CLOCK;
//       break;
//     case KEY_DOWN:
//       this->move = TM_DROP;
//       break;
//     case 'q':
//       *running = false;
//       this->move = TM_NONE;
//       break;
//     case 'p':
//       wclear(this->interface.board);
//       box(this->interface.board, 0, 0);
//       wmove(this->interface.board, this->tg->rows/2, (this->tg->cols*COLS_PER_CELL-6)/2);
//       wprintw(this->interface.board, "PAUSED");
//       wrefresh(this->interface.board);
//       timeout(-1);
//       getch();
//       timeout(0);
//       this->move = TM_NONE;
//       break;
//     case ' ':
//       this->move = TM_HOLD;
//       break;
//     default:
//       this->move = TM_NONE;
//     }
//   }

//   void finish(){
//     // Deinitialize NCurses
//     wclear(stdscr);
//     endwin();

//     // Output ending message.
//     printf("Game over!\n");
//     printf("You finished with %d points on level %d.\n", this->tg->points, this->tg->level);

//     // Deinitialize Tetris
//     tg_delete(this->tg);
//   }

//   /*
//     Do the NCURSES initialization steps for color blocks.
//    */
//   void init_colors(void)
//   {
//     start_color();
//     init_pair(TC_CELLI, COLOR_CYAN, COLOR_BLACK);
//     init_pair(TC_CELLJ, COLOR_BLUE, COLOR_BLACK);
//     init_pair(TC_CELLL, COLOR_WHITE, COLOR_BLACK);
//     init_pair(TC_CELLO, COLOR_YELLOW, COLOR_BLACK);
//     init_pair(TC_CELLS, COLOR_GREEN, COLOR_BLACK);
//     init_pair(TC_CELLT, COLOR_MAGENTA, COLOR_BLACK);
//     init_pair(TC_CELLZ, COLOR_RED, COLOR_BLACK);
//   }

//   Game(){
//     // create new game.
//     this->tg = tg_create(22, 10);

//     // NCURSES initialization:
//     initscr();             // initialize curses
//     cbreak();              // pass key presses to program, but not signals
//     noecho();              // don't echo key presses to screen
//     keypad(stdscr, TRUE);  // allow arrow keys
//     timeout(0);            // no blocking on getch()
//     curs_set(0);           // set the cursor to invisible
//     init_colors();         // setup tetris colors

//     // this->interface = Interface( this->tg );
//   }
// };


/*
  Main tetris game!
 */
int main()
{

  bool running = true;

  Game game = Game();

  // Game loop
  while (running) {
    // running = tg_tick(game.tg, game.move);

    game.interface.display_update( game.tg, game.move, &running );

    game.get_command( &running );
  }

  game.finish();

  return 0;
}
