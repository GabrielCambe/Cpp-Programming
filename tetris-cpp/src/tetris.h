/***************************************************************************//**

  @file         tetris.h

  @author       Stephen Brennan

  @date         Created Wednesday, 10 June 2015

  @brief        Tetris game declarations.

  @copyright    Copyright (c) 2015, Stephen Brennan.  Released under the Revised
                BSD License.  See LICENSE.txt for details.

*******************************************************************************/

#ifndef TETRIS_H
#define TETRIS_H
// #pragma once

#include <iostream>
// #include <cstdio>
// #include <stdio.h> // for FILE
#include <cstdbool> // for bool
// #include <stdbool.h> // for bool


#include "util.h"

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





/*
  Convert a tetromino type to its corresponding cell.
 */
#define TYPE_TO_CELL(x) ((x)+1)

/*
  Strings for how you would print a tetris board.
 */
#define TC_EMPTY_STR " "
#define TC_BLOCK_STR "\u2588"

/*
  Questions about a tetris cell.
 */
#define TC_IS_EMPTY(x) ((x) == TC_EMPTY)
#define TC_IS_FILLED(x) (!TC_IS_EMPTY(x))

/*
  How many cells in a tetromino?
 */
#define TETRIS 4
/*
  How many tetrominos?
 */
#define NUM_TETROMINOS 7
/*
  How many orientations of a tetromino?
 */
#define NUM_ORIENTATIONS 4

/*
  Level constants.
 */
#define MAX_LEVEL 19
#define LINES_PER_LEVEL 10

/*
  A "cell" is a 1x1 block within a tetris board.
 */
typedef enum {
  TC_EMPTY, TC_CELLI, TC_CELLJ, TC_CELLL, TC_CELLO, TC_CELLS, TC_CELLT, TC_CELLZ
} tetris_cell;

/*
  A "type" is a type/shape of a tetromino.  Not including orientation.
 */
typedef enum {
  TET_I, TET_J, TET_L, TET_O, TET_S, TET_T, TET_Z
} tetris_type;

/*
  A row,column pair.  Negative numbers allowed, because we need them for
  offsets.
 */
typedef struct {
  int row;
  int col;
} tetris_location;

/*
  A "block" is a struct that contains information about a tetromino.
  Specifically, what type it is, what orientation it has, and where it is.
 */
typedef struct {
  int typ;
  int ori;
  tetris_location loc;
} tetris_block;

/*
  All possible moves to give as input to the game.
 */
typedef enum {
  TM_LEFT, TM_RIGHT, TM_CLOCK, TM_COUNTER, TM_DROP, TM_HOLD, TM_NONE
} tetris_move;

/*
  A game object!
 */
typedef struct {
  /*
    Game board stuff:
   */
  int rows;
  int cols;
  char *board;
  /*
    Scoring information:
   */
  int points;
  int level;
  /*
    Falling block is the one currently going down.  Next block is the one that
    will be falling after this one.  Stored is the block that you can swap out.
   */
  tetris_block falling;
  tetris_block next;
  tetris_block stored;
  /*
    Number of game ticks until the block will move down.
   */
  int ticks_till_gravity;
  /*
    Number of lines until you advance to the next level.
   */
  int lines_remaining;
} tetris_game;

/*
  This array stores all necessary information about the cells that are filled by
  each tetromino.  The first index is the type of the tetromino (i.e. shape,
  e.g. I, J, Z, etc.).  The next index is the orientation (0-3).  The final
  array contains 4 tetris_location objects, each mapping to an offset from a
  point on the upper left that is the tetromino "origin".
 */
extern tetris_location TETROMINOS[NUM_TETROMINOS][NUM_ORIENTATIONS][TETRIS];

/*
  This array tells you how many ticks per gravity by level.  Decreases as level
  increases, to add difficulty.
 */
extern int GRAVITY_LEVEL[MAX_LEVEL+1];

// Data structure manipulation.
void tg_init(tetris_game *obj, int rows, int cols);
tetris_game *tg_create(int rows, int cols);
void tg_destroy(tetris_game *obj);
void tg_delete(tetris_game *obj);
tetris_game *tg_load(FILE *f);
void tg_save(tetris_game *obj, FILE *f);

// Public methods not related to memory:
char tg_get(tetris_game *obj, int row, int col);
bool tg_check(tetris_game *obj, int row, int col);
bool tg_tick(tetris_game *obj, tetris_move move);
void tg_print(tetris_game *obj, FILE *f);

class Interface{
  public:
    WINDOW *board, *next, *hold, *score;

    /*
      Print the tetris board onto the ncurses window.
     */
    void display_board(WINDOW *w, tetris_game *obj)
    {
      int i, j;
      box(w, 0, 0);
      for (i = 0; i < obj->rows; i++) {
        wmove(w, 1 + i, 1);
        for (j = 0; j < obj->cols; j++) {
          if (TC_IS_FILLED(tg_get(obj, i, j))) {
            ADD_BLOCK(w,tg_get(obj, i, j));
          } else {
            ADD_EMPTY(w);
          }
        }
      }
      wnoutrefresh(w);
    }

    /*
      Display a tetris piece in a dedicated window.
    */
    void display_piece(WINDOW *w, tetris_block block)
    {
      int b;
      tetris_location c;
      wclear(w);
      box(w, 0, 0);
      if (block.typ == -1) {
        wnoutrefresh(w);
        return;
      }
      for (b = 0; b < TETRIS; b++) {
        c = TETROMINOS[block.typ][block.ori][b];
        wmove(w, c.row + 1, c.col * COLS_PER_CELL + 1);
        ADD_BLOCK(w, TYPE_TO_CELL(block.typ));
      }
      wnoutrefresh(w);
    }

    /*
      Display score information in a dedicated window.
     */
    void display_score(WINDOW *w, tetris_game *tg)
    {
      wclear(w);
      box(w, 0, 0);
      wprintw(w, "Score\n%d\n", tg->points);
      wprintw(w, "Level\n%d\n", tg->level);
      wprintw(w, "Lines\n%d\n", tg->lines_remaining);
      wnoutrefresh(w);
    }


    void display_update( tetris_game *tg, tetris_move move, bool *running ){
      *running = tg_tick(tg, move);
      display_board(this->board, tg);
      display_piece(this->next, tg->next);
      display_piece(this->hold, tg->stored);
      display_score(this->score, tg);
      doupdate();
      sleep_milli(10);
    }

    Interface( tetris_game *tg ){
      // Create windows for each section of the interface.
      this->board = newwin(tg->rows + 2, 2 * tg->cols + 2, 0, 0);
      this->next  = newwin(6, 10, 0, 2 * (tg->cols + 1) + 1);
      this->hold  = newwin(6, 10, 7, 2 * (tg->cols + 1) + 1);
      this->score = newwin(6, 10, 14, 2 * (tg->cols + 1 ) + 1);
    }
};


class Game{
  public:
    tetris_game *tg;
    tetris_move move = TM_NONE;
    Interface interface = Interface( this->tg );

  void get_command( bool *running ){
    switch (getch()) {
    case KEY_LEFT:
      this->move = TM_LEFT;
      break;
    case KEY_RIGHT:
      this->move = TM_RIGHT;
      break;
    case KEY_UP:
      this->move = TM_CLOCK;
      break;
    case KEY_DOWN:
      this->move = TM_DROP;
      break;
    case 'q':
      *running = false;
      this->move = TM_NONE;
      break;
    case 'p':
      wclear(this->interface.board);
      box(this->interface.board, 0, 0);
      wmove(this->interface.board, this->tg->rows/2, (this->tg->cols*COLS_PER_CELL-6)/2);
      wprintw(this->interface.board, "PAUSED");
      wrefresh(this->interface.board);
      timeout(-1);
      getch();
      timeout(0);
      this->move = TM_NONE;
      break;
    case ' ':
      this->move = TM_HOLD;
      break;
    default:
      this->move = TM_NONE;
    }
  }

  void finish(){
    // Deinitialize NCurses
    wclear(stdscr);
    endwin();

    // Output ending message.
    printf("Game over!\n");
    printf("You finished with %d points on level %d.\n", this->tg->points, this->tg->level);

    // Deinitialize Tetris
    tg_delete(this->tg);
  }

  /*
    Do the NCURSES initialization steps for color blocks.
   */
  void init_colors(void)
  {
    start_color();
    init_pair(TC_CELLI, COLOR_CYAN, COLOR_BLACK);
    init_pair(TC_CELLJ, COLOR_BLUE, COLOR_BLACK);
    init_pair(TC_CELLL, COLOR_WHITE, COLOR_BLACK);
    init_pair(TC_CELLO, COLOR_YELLOW, COLOR_BLACK);
    init_pair(TC_CELLS, COLOR_GREEN, COLOR_BLACK);
    init_pair(TC_CELLT, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(TC_CELLZ, COLOR_RED, COLOR_BLACK);
  }

  Game(){
    // create new game.
    this->tg = tg_create(22, 10);

    // NCURSES initialization:
    initscr();             // initialize curses
    cbreak();              // pass key presses to program, but not signals
    noecho();              // don't echo key presses to screen
    keypad(stdscr, TRUE);  // allow arrow keys
    timeout(0);            // no blocking on getch()
    curs_set(0);           // set the cursor to invisible
    init_colors();         // setup tetris colors

    // this->interface = Interface( this->tg );
  }
};


#endif // TETRIS_H

