/* A simple program to learn
   more C and using ncurses */

#include <ncurses.h>
#include <unistd.h> // For sleep?
#include <string.h>
#include <stdlib.h>

// Function for reading CPU temperatur from file.
int readTemp()
{
  const char *TEMPFILE = "/sys/class/hwmon/hwmon1/temp1_input";
  FILE *fp             = fopen(TEMPFILE, "r");

  if (fp == NULL)
  {
    // TO DO: add error message
    return -666;  }

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
    return -666;
  } 
}

// Function for printing temperature to screen.
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

// Function for drawing border.
void drawBorderAndMessage(int x, int y, const char *message)
{
  int len   = strlen(message);
  int width = len + 16; // Padding, change if needed.

  // Colors, colors, colors...
  attron(COLOR_PAIR(1));
  // Draw border with message in it (top).
  move(0, 0);
  for (int i = 0; i < 7; i++)
  {
    addch('#');
  }
  move(x, y);
  printw("%s", message);

  move(x, y+len+1);
  for (int i = 0; i < 7; i++)
  {
    addch('#');
  }

  int bx = 1; // Variable for left right border.
  // Draw left right border.
  for (int i = 0; i < 3; i++)
  {
    move(bx, 0);
    addch('#');
    move(bx, width-1);
    addch('#');
    bx++;
  }
  
  // Draw bottom border.
  move(4, 0);
  for (int i = 0; i < width; i++)
  {
    addch('#');
  }
  attroff(COLOR_PAIR(1));
}


int main(void)
{
  initscr();
  keypad(stdscr, TRUE);  // True means to enable.
  noecho();
  nodelay(stdscr, TRUE); // Black magic...
  start_color();         // Starting color festival.

  // Define color pair 1: Red text, default background.
  init_pair(1, COLOR_RED, COLOR_BLACK);

  // Variables for closing program
  // and setting location of text
  int key      = 0;
  int temp_x   = 2;
  int temp_y   = 3;

  while (key != 'q')
  {
    clear();

    // Trying to draw border and display message
    drawBorderAndMessage(0, 8, "Press 'Q' to quit.");

    printTemp(temp_x, temp_y);

    sleep(1);
    key = getch(); // Get user input.
  }
  
  endwin();
  return 0;
}
