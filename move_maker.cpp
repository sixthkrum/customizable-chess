#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <array>
#include <vector>
#include <string>

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
/* xxxx0000 binary */
#define TAKE_MOVE 0x16

// first four bits tell the direction of the take w.r.t position of the piece on landing


struct piece_info
{
  char name [ 8 ];
  unsigned int starting_position [ 2 ];
  std::vector < std::array < unsigned int , 3 > > moveset; // 0 , 1 -> y , x pos | 2 move attributes
  std::vector < std::array < unsigned int , 4 > > special_behaviour; // 3 type of behaviour | 0 , 1 , 2 variables
  char img [ 4 ];
};

bool initialize_window ( WINDOW *w = stdscr )
{
  if ( w != NULL )
  {
    keypad ( w , TRUE );
    nodelay ( w , TRUE );
    noecho();
    raw();
    curs_set ( 2 );

    return 1;
  }

  return 0;
}

bool mark_center ( WINDOW *w = stdscr )
{
  if ( w != NULL )
  {
    int maxY , maxX;
    getmaxyx ( w , maxY , maxX );
    int centerY = maxY / 2;
    int centerX = maxX / 2;
    mvwprintw ( w , centerY , centerX , "x");
    wrefresh ( w );

    return 1;
  }

  return 0;
}

/* 0 , 0 is the coordinate of the top left of board */

bool make_chessboard ( WINDOW *w = stdscr )
{
  if ( w != NULL )
  {
    int maxY , maxX;
    getmaxyx ( w , maxY , maxX );

    if ( maxX >= 42 && maxY >= 17 )
    {
      mvwprintw ( w , 0 , 0 , "\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------\n\
|    |    |    |    |    |    |    |    |\n\
-----------------------------------------");
      wrefresh ( w );

      return 1;
    }

    else
    {
      mvwprintw ( w , 0 , 0 , "screen must be at least 42 x 17, press q to quit\n" );
      wrefresh ( w );

      return 0;
    }
  }

  return 0;
}

bool move_editor ( WINDOW *w = stdscr )
{
  if ( w != NULL )
  {
    int maxY , maxX;
    getmaxyx ( w , maxY , maxX );
    int currentY = 0;
    int currentX = 0;

    int input;

    do {
      input = wgetch( w );

      switch ( input )
      {
        case KEY_UP:

        if ( currentY - 1 >= 0 )
        {
          currentY --;
        }

        else
        {
          currentY = maxY - 1;
        }

        wmove ( stdscr , currentY , currentX );

        break;


        case KEY_DOWN:

        if ( currentY + 1 <= maxY - 1 )
        {
          currentY ++;
        }

        else
        {
          currentY = 0;
        }

        wmove ( stdscr , currentY , currentX );

        break;


        case KEY_LEFT:

        if ( currentX - 1 >= 0 )
        {
          currentX --;
        }

        else
        {
          currentX = maxX - 1;
        }

        wmove ( stdscr , currentY , currentX );

        break;


        case KEY_RIGHT:

        if ( currentX + 1 <= maxX - 1 )
        {
          currentX ++;
        }

        else
        {
          currentX = 0;
        }

        wmove ( stdscr , currentY , currentX );

        break;


        case 'o': case 'O':

        getyx ( stdscr , currentY , currentX );

        printw ( "O" , stdscr );

        break;


        case 's': case 'S':

        clear();
        refresh();

        make_chessboard();

        break;


        default:

        break;

      }

      refresh();

    } while(input != 'q' && input != 'Q');

    return 1;
  }

  return 0;
}

int main()
{
  initscr();
  initialize_window();
  mark_center();

  move_editor();
  endwin();
}
