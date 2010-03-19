/* 

Game of Life - the classic cellular automata demo

Copyright © 2003  Matti Pöllä

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


Compilation using the GCC compiler:

  gcc -Wall -lcurses -o gameoflife gameoflife.c

*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

/* Check whether all cells are dead */
int gameover (int grid[COLS][LINES])
{
  int i;
  int j;
  int alive;
  alive = 0;

  for (i = 0; i < COLS; i++)
    {
      for (j = 0; j < LINES; j++)
	{
	  if (grid[i][j] == 1)
	    return 1;
	}
    }
  return 0;
}

/* Initiate grid */
void init_life (int grid[COLS][LINES])
{
  int i;
  int j;

  srandom(time(0) * getpid());

  for (i = 0; i < COLS; i++)
    {
      for (j = 0; j < LINES; j++)
	{
	  if ((rand() % 3) == 0)
	    grid[i][j] = 1;
	  else
	    grid[i][j] = 0;
	}
    }
}

/* 
 * Perform a single iteration of the game of life.
 */
void run_life (int grid[COLS][LINES])
{
  int i;       // row position
  int j;       // column position
  int ii;      // left
  int jj;      // down
  int iii;     // right
  int jjj;     // up
  int nei = 0; // number of neighbors

  int newgrid[COLS][LINES];

  for (i = 0; i < COLS; i++)
    {
      for (j = 0; j < LINES; j++)
	{
	  if (i-1 < 0)
	    ii = COLS-1;
	  else
	    ii = i-1;

	  if (i+1 >= COLS)
	    iii = 0;
	  else
	    iii = i+1;


	  if (j-1 < 0)
	    jj = LINES-1;
	  else
	    jj = j-1;
	  
	  if (j+1 >= LINES)
	    jjj = 0;
	  else
	    jjj = j+1;
	    
	  nei = 0;
	  nei += grid[ii][jj];
	  nei += grid[ii][j];
	  nei += grid[ii][jjj];
	  nei += grid[i][jj];
	  nei += grid[i][jjj];
	  nei += grid[iii][jj];
	  nei += grid[iii][j];
	  nei += grid[iii][jjj];

	  // Game of Life rules

	  // Exactly three neighbors - cell comes alive
	  if ((grid[i][j] == 0) && nei == 3)
	    newgrid[i][j] = 1;
	  // Two or three neighbors - cell stays alive
	  else if ((grid[i][j] == 1) && (nei == 3 || nei == 2))
	    newgrid[i][j] = 1;
	  // Otherwise cell dies by overcrowdedness or remains dead
	  else
	    newgrid[i][j] = 0;
	}
    }

  for (i = 0; i < COLS; i++)
    {
      for (j = 0; j < LINES; j++)
	{
	  grid[i][j] = newgrid[i][j];
	}
    }
  
}

/* 
 * Display the grid 
 **/
void printgrid (int grid[COLS][LINES])
{
  int i;
  int j;

  for (i = 0; i < COLS; i++)
    {
      for (j = 0; j < LINES; j++)
	{
	  move(j, i);
	  if (grid[i][j] == 0) {
	    addch(' ');
	  }
	  else if (grid[i][j] == 1) {
	    addch('*');
	  }
	}
    }
}

int main(void)
{
  initscr();
  noecho();
  noecho();
  curs_set(0); 

  int grid[COLS][LINES];

  init_life (grid);
  printgrid (grid);
  
  for (;;)
    {
      run_life (grid);
      printgrid (grid);
      refresh();
      if (gameover(grid) == 0)
	break;
      usleep (50000);
    }

  refresh();
  endwin();
  return 0;
}
