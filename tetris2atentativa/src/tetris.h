/***************************************************************************//**

  @file         tetris.h

  @author       Stephen Brennan

  @date         Created Wednesday, 10 June 2015

  @brief        Tetris game declarations.

  @copyright    Copyright (c) 2015, Stephen Brennan.  Released under the Revised
                BSD License.  See LICENSE.txt for details.

*******************************************************************************/

// #ifndef TETRIS_H
// #define TETRIS_H

#pragma once

#include <cstdio>
//#include <stdio.h> // for FILE
#include <cstdbool>
//#include <stdbool.h> // for bool
#include <cstdlib>
#include <cstring>
#include <ctime>

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

/*
  Return a random tetromino type.
 */
static int random_tetromino(void) {
  return rand() % NUM_TETROMINOS;
}

/*  A game object!  */
class TetrisGame {
  public:
    /*  Game board stuff:  */
    int rows;
    int cols;
    char *board;
    /*  Scoring information:  */
    int points;
    int level;
    /*  Falling block is the one currently going down.  Next block is the one that
      will be falling after this one.  Stored is the block that you can swap out.  */
    tetris_block falling;
    tetris_block next;
    tetris_block stored;
    /*  Number of game ticks until the block will move down.  */
    int ticks_till_gravity;
    /*  Number of lines until you advance to the next level.  */
    int lines_remaining;

  //private:
    bool tg_check(TetrisGame *obj, int row, int col);
    void tg_set(TetrisGame *obj, int row, int column, char value);
    void tg_new_falling(TetrisGame *obj);
    void tg_remove(TetrisGame *obj, tetris_block block);
    bool tg_fits(TetrisGame *obj, tetris_block block);
    void tg_put(TetrisGame *obj, tetris_block block);
    void tg_hold(TetrisGame *obj);
    void tg_rotate(TetrisGame *obj, int direction);
    void tg_down(TetrisGame *obj);
    void tg_move(TetrisGame *obj, int direction);
    void tg_handle_move(TetrisGame *obj, tetris_move move);
    void tg_do_gravity_tick(TetrisGame *obj);


  //public:
    // Data structure manipulation.
    void tg_save(TetrisGame *obj, FILE *f);
    TetrisGame *tg_load(FILE *f);

    // Public methods not related to memory:
    char tg_get(TetrisGame *obj, int row, int col);
    bool tg_tick(TetrisGame *obj, tetris_move move);
    void tg_print(TetrisGame *obj, FILE *f);

    TetrisGame( int rows, int cols ){
      // Initialization logic
      this->rows = rows;
      this->cols = cols;
      this->board = (char*) std::malloc((rows * cols)*(sizeof(char)));
      std::memset(this->board, TC_EMPTY, rows * cols);
      this->points = 0;
      this->level = 0;
      this->ticks_till_gravity = GRAVITY_LEVEL[this->level];
      this->lines_remaining = LINES_PER_LEVEL;
      srand(std::time(NULL));
      tg_new_falling(this);
      tg_new_falling(this);
      this->stored.typ = -1;
      this->stored.ori = 0;
      this->stored.loc.row = 0;
      this->next.loc.col = this->cols/2 - 2;
      std::printf("%d", this->falling.loc.col);
    }
    // void tg_init(tetris_game *obj, int rows, int cols);
    // tetris_game *tg_create(int rows, int cols); // Constructor
    
    ~TetrisGame(){
      // Cleanup logic
      std::free(this->board);
      // Output ending message.
      std::printf("Game over!\n");
      std::printf("You finished with %d points on level %d.\n", this->points, this->level);    
    }
    // void tg_destroy(tetris_game *obj); // Destroyer
    // void tg_delete(tetris_game *obj); // Deleter?
};

// #endif // TETRIS_H
