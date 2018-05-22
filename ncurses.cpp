#include <unistd.h>
#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 



auto init_color_pairs () -> void // To initialise all colors using a easy-to-memorize naming scheme.
{
        short f, b; // For foreground and background respectively.
        for ( f = 0; f < COLORS; ++f )
        {
                for ( b = 0; b < COLORS; ++b )
                {
                        init_pair ( f * COLORS + b, f, b );
                }
        }
}

int main(){
	unsigned int mili = 1; 
	char mesg[]="Just a string";		/* message to be appeared on the screen */
	int row,col;				/* to store the number of rows and *
						 * the number of colums of the screen */
	initscr();				/* start the curses mode */
	raw();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	curs_set(0);
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	attron(COLOR_PAIR(2));
	mvprintw(1,(col-strlen(mesg))/2,"%s",mesg);
                                	/* print the message at the center of the screen */
	attron(COLOR_PAIR(1));
	mvprintw(3,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again\n");

	move(4,0);
	clrtoeol();

	int i = 0;
	attron(COLOR_PAIR(2));
	refresh();
	while(i < 20){
		sleep(mili);
		addch(' ');
		refresh();
		i++;
	}
	getch();
	endwin();

	return 0;
}