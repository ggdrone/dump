/* A simple program to learn
   more C and using ncurses */

#include <ncurses.h>

// Function for reading CPU temperatur from file.
int readTemp()
{
  const char *TEMPFILE = "/sys/class/hwmon/hwmon1/temp1_input";
  FILE *fp             = fopen(TEMPFILE, "r");

  if (fp == NULL)
  {
    // TO DO: add error message
    return -1;
  }

  char buffer[256];
  if (fgets(buffer, sizeof(buffer), fp))
  {
    fclose(fp);
    return atoi(buffer) / 1000.0; // atoi converts str to int
  }
  else
  {
    // TO DO: add error message
    fclose(fp);
    return -1;
  } 
}

// Function for printing temperature to screen
float printTemp(int x, int y)
{
  float temp = readTemp(); // Get the temperature.
  move(x, y); // Moves cursor to determined pos.

  if (temp < 0)
  {
    printw("ERROR: could not read temperature! Wrong file?");
  }
  else
  {
    printw("CPU temperature is: %.2f *C", temp);
  }

  refresh(); // Refresh screen to update content.
  return 0;
}

int main(void)
{
  initscr();
  keypad(stdscr, TRUE); // True means to enable.
  noecho();
  nodelay(stdscr, TRUE); // Black magic...

  // Variables for closing program
  // and setting location of text
  int key = 0;
  int x   = 2;
  int y   = 3;

  while (key != 'q')
  {
    clear();
    move(0, 0);
    printw("Press 'Q' to quit.");

    printTemp(x, y);

    sleep(1);
    key = getch(); // Get user input.
  }
  
  endwin();
  return 0;
}
