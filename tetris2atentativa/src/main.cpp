/***************************************************************************//**

  @file         main.c

  @author       Stephen Brennan

  @date         Created Wednesday, 10 June 2015

  @brief        Main program for tetris.

  @copyright    Copyright (c) 2015, Stephen Brennan.  Released under the Revised
                BSD License.  See LICENSE.txt for details.

*******************************************************************************/
#include <cstdbool>
#include <ctime>

#include "tetris.h"
#include "util.h"
#include "interface.h"

/*
  Main tetris game!
 */
int main()
{
  // create new game.
  TetrisGame tg = TetrisGame(22, 10);

  
  tetris_move move = TM_NONE;
  bool running = true;

  Interface interface = Interface( tg->rows, tg->cols );

  // Game loop
  while (running) {
    running = tg->tg_tick(tg, move);
  
    interface.display_game(tg);
  
    sleep_milli(10);

    interface.get_command(getch());


  }

  // tg and interface are destroyed
  // ncurses deinitializate and the game over message goes up
  return 0;
}
