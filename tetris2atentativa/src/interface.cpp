#include <ncurses.h>

#include "interface.h"
#include "tetris.h"

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

void Interface::get_command(char cmd){
    switch (cmd) {
        case KEY_LEFT:
            move = TM_LEFT;
            break;
        case KEY_RIGHT:
            move = TM_RIGHT;
            break;
        case KEY_UP:
            move = TM_CLOCK;
            break;
        case KEY_DOWN:
            move = TM_DROP;
            break;
        case 'q':
            running = false;
            move = TM_NONE;
            break;
        case 'p':
            wclear(board);
            box(board, 0, 0);
            wmove(board, tg->rows/2, (tg->cols*COLS_PER_CELL-6)/2);
            wprintw(board, "PAUSED");
            wrefresh(board);
            timeout(-1);
            getch();
            timeout(0);
            move = TM_NONE;
            break;
        case ' ':
            move = TM_HOLD;
            break;
        default:
            move = TM_NONE;
    }
}

void Interface::display_game( TetrisGame *tg ){
    display_board(this->board, tg);
    display_piece(this->next, tg->next);
    display_piece(this->hold, tg->stored);
    display_score(this->score, tg);
    doupdate();
}

void Interface::do_update(){

}