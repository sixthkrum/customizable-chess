#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <array>
#include <vector>

/* 00000000 binary */
#define STANDALONE_MOVE 0x0
/* 00000001 binary */
#define HORIZONTAL_MOVE 0x1
/* 00000010 binary */
#define VERTICAL_MOVE 0x2
/* 00000100 binary */
#define LEFTDIAGNOL_MOVE 0x4
/* 00001000 binary */
#define RIGHTDIAGNOL_MOVE 0x8
/* 00010000 binary */
#define TAKE_MOVE 0x16

bool mark_center ( WINDOW *w = stdscr )
{
  if ( w != NULL )
  {
    int maxY , maxX;
    getmaxyx (stdscr , maxY , maxX);
    int centerY = maxY / 2;
    int centerX = maxX / 2;
    mvwprintw ( w , centerY , centerX , "x");
    wrefresh ( w );

    return 1;
  }

  return 0;
}

int main()
{
  initscr();
  keypad(stdscr , TRUE);
  nodelay(stdscr , TRUE);
  noecho();
  raw();
  curs_set(2);

  mark_center();

  int maxY , maxX;
  getmaxyx(stdscr , maxY , maxX);
  int currentY = maxY / 2;
  int currentX = maxX / 2;

  int input;

  std::array < std::vector < std::array < unsigned int , 2 > > , 16 > movesets;
  short int piece_index = 0;

  do {
    input = getch();

    switch(input)
    {
      case KEY_UP:
      if(currentY - 1 >= 0)
      {
        currentY--;
      }
      wmove(stdscr , currentY , currentX);
      break;

      case KEY_DOWN:
      if(currentY + 1 <= maxY - 1)
      {
        currentY++;
      }
      wmove(stdscr , currentY , currentX);
      break;

      case KEY_LEFT:
      if(currentX - 1 >= 0)
      {
        currentX--;
      }
      wmove(stdscr , currentY , currentX);
      break;

      case KEY_RIGHT:
      if(currentX + 1 <= maxX - 1)
      {
        currentX++;
      }
      wmove(stdscr , currentY , currentX);
      break;

      case '#':
      printw("%c" , input , stdscr);
      if(currentX + 1 <= maxX - 1)
      {
        currentX++;
      }
      break;

      case 's':

      default:
      break;
    }

    refresh();
  } while(input != 'q' && input != 'Q');

  endwin();
}
