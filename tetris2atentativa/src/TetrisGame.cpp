#include "tetris.h"

/*
  Check whether a row and column are in bounds.
 */
bool TetrisGame::tg_check(TetrisGame *obj, int row, int col)
{
  return 0 <= row && row < obj->rows && 0 <= col && col < obj->cols;
}

/*
  Set the block at the given row and column.
 */
/*static*/ void TetrisGame::tg_set(TetrisGame *obj, int row, int column, char value)
{
  obj->board[obj->cols * row + column] = value;
}

/*
  Create a new falling block and populate the next falling block with a random
  one.
 */
/*static*/ void TetrisGame::tg_new_falling(TetrisGame *obj)
{
  // Put in a new falling tetromino.
  obj->falling = obj->next;
  obj->next.typ = random_tetromino();
  obj->next.ori = 0;
  obj->next.loc.row = 0;
  obj->next.loc.col = obj->cols/2 - 2;
}

/*
  Clear a block out of the board.
 */
/*static*/ void TetrisGame::tg_remove(TetrisGame *obj, tetris_block block)
{
  int i;
  for (i = 0; i < TETRIS; i++) {
    tetris_location cell = TETROMINOS[block.typ][block.ori][i];
    tg_set(obj, block.loc.row + cell.row, block.loc.col + cell.col, TC_EMPTY);
  }
}

/*
  Check if a block can be placed on the board.
 */
/*static*/ bool TetrisGame::tg_fits(TetrisGame *obj, tetris_block block)
{
  int i, r, c;
  for (i = 0; i < TETRIS; i++) {
    tetris_location cell = TETROMINOS[block.typ][block.ori][i];
    r = block.loc.row + cell.row;
    c = block.loc.col + cell.col;
    if (!tg_check(obj, r, c) || TC_IS_FILLED(tg_get(obj, r, c))) {
      return false;
    }
  }
  return true;
}

/*
  Place a block onto the board.
 */
/*static*/ void TetrisGame::tg_put(TetrisGame *obj, tetris_block block)
{
  int i;
  for (i = 0; i < TETRIS; i++) {
    tetris_location cell = TETROMINOS[block.typ][block.ori][i];
    tg_set(obj, block.loc.row + cell.row, block.loc.col + cell.col,
           TYPE_TO_CELL(block.typ));
  }
}

/*
  Swap the falling block with the block in the hold buffer.
 */
/*static*/ void TetrisGame::tg_hold(TetrisGame *obj)
{
  tg_remove(obj, obj->falling);
  if (obj->stored.typ == -1) {
    obj->stored = obj->falling;
    tg_new_falling(obj);
  } else {
    int typ = obj->falling.typ, ori = obj->falling.ori;
    obj->falling.typ = obj->stored.typ;
    obj->falling.ori = obj->stored.ori;
    obj->stored.typ = typ;
    obj->stored.ori = ori;
    while (!tg_fits(obj, obj->falling)) {
      obj->falling.loc.row--;
    }
  }
  tg_put(obj, obj->falling);
}

/*
  Rotate the falling block in either direction (+/-1).
 */
/*static*/ void TetrisGame::tg_rotate(TetrisGame *obj, int direction)
{
  tg_remove(obj, obj->falling);

  while (true) {
    obj->falling.ori = (obj->falling.ori + direction) % NUM_ORIENTATIONS;

    // If the new orientation fits, we're done.
    if (tg_fits(obj, obj->falling))
      break;

    // Otherwise, try moving left to make it fit.
    obj->falling.loc.col--;
    if (tg_fits(obj, obj->falling))
      break;

    // Finally, try moving right to make it fit.
    obj->falling.loc.col += 2;
    if (tg_fits(obj, obj->falling))
      break;

    // Put it back in its original location and try the next orientation.
    obj->falling.loc.col--;
    // Worst case, we come back to the original orientation and it fits, so this
    // loop will terminate.
  }

  tg_put(obj, obj->falling);
}


/*
  Send the falling tetris block to the bottom.
 */
/*static*/ void TetrisGame::tg_down(TetrisGame *obj)
{
  tg_remove(obj, obj->falling);
  while (tg_fits(obj, obj->falling)) {
    obj->falling.loc.row++;
  }
  obj->falling.loc.row--;
  tg_put(obj, obj->falling);
  tg_new_falling(obj);
}

/*
  Move the falling tetris block left (-1) or right (+1).
 */
/*static*/ void TetrisGame::tg_move(TetrisGame *obj, int direction)
{
  tg_remove(obj, obj->falling);
  obj->falling.loc.col += direction;
  if (!tg_fits(obj, obj->falling)) {
    obj->falling.loc.col -= direction;
  }
  tg_put(obj, obj->falling);
}

/*
  Perform the action specified by the move.
 */
/*static*/ void Tetris::tg_handle_move(TetrisGame *obj, tetris_move move)
{
  switch (move) {
  case TM_LEFT:
    tg_move(obj, -1);
    break;
  case TM_RIGHT:
    tg_move(obj, 1);
    break;
  case TM_DROP:
    tg_down(obj);
    break;
  case TM_CLOCK:
    tg_rotate(obj, 1);
    break;
  case TM_COUNTER:
    tg_rotate(obj, -1);
    break;
  case TM_HOLD:
    tg_hold(obj);
    break;
  default:
    // pass
    break;
  }
}

/*
  Tick gravity, and move the block down if gravity should act.
 */
/*static*/ void TetrisGame::tg_do_gravity_tick(TetrisGame *obj)
{
  obj->ticks_till_gravity--;
  if (obj->ticks_till_gravity <= 0) {
    tg_remove(obj, obj->falling);
    obj->falling.loc.row++;
    if (tg_fits(obj, obj->falling)) {
      obj->ticks_till_gravity = GRAVITY_LEVEL[obj->level];
    } else {
      obj->falling.loc.row--;
      tg_put(obj, obj->falling);

      tg_new_falling(obj);
    }
    tg_put(obj, obj->falling);
  }
}

/*
  Save a game to a file.
 */
void TetrisGame::tg_save(TetrisGame *obj, FILE *f)
{
  std::fwrite(obj, sizeof(TetrisGame), 1, f);
  std::fwrite(obj->board, sizeof(char), obj->rows * obj->cols, f);
}

/*
  Load a game from a file.
 */
TetrisGame *TetrisGame::tg_load(FILE *f)
{
  TetrisGame *obj = (TetrisGame*) std::malloc(sizeof(TetrisGame));
  std::fread(obj, sizeof(TetrisGame), 1, f);
  obj->board = (char*) std::malloc(obj->rows * obj->cols);
  std::fread(obj->board, sizeof(char), obj->rows * obj->cols, f);
  return obj;
}

/*
   Return the block at the given row and column.
 */
char TetrisGame::tg_get(TetrisGame *obj, int row, int column)
{
  return obj->board[obj->cols * row + column];
}

/*
  Do a single game tick: process gravity, user input, and score.  Return true if
  the game is still running, false if it is over.
 */
bool TetrisGame::tg_tick(TetrisGame *obj, tetris_move move)
{
  int lines_cleared;
  // Handle gravity.
  tg_do_gravity_tick(obj);

  // Handle input.
  tg_handle_move(obj, move);

  // Check for cleared lines
  lines_cleared = tg_check_lines(obj);

  tg_adjust_score(obj, lines_cleared);

  // Return whether the game will continue (NOT whether it's over)
  return !tg_game_over(obj);
}

/*
  Print a game board to a file.  Really just for early debugging.
 */
void TetrisGame::tg_print(TetrisGame *obj, FILE *f) {
  int i, j;
  for (i = 0; i < obj->rows; i++) {
    for (j = 0; j < obj->cols; j++) {
      if (TC_IS_EMPTY(tg_get(obj, i, j))) {
        fputs(TC_EMPTY_STR, f);
      } else {
        fputs(TC_BLOCK_STR, f);
      }
    }
    fputc('\n', f);
  }
}