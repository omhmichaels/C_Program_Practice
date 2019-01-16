#include <termios.h>
#include <unistd.h>

// Set teminal attributs by using tcgetattr()
//   > Read the current atrributes into a struct
//   > modify the struct by hand
//   > pass modified struct to tcsetattr()
//   > write the new attributes back out

void enableRawMode(){
  struct termios raw;

  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO. &raw);
}




int main(){
  char c;
  while (read(STDIN_FILENO, &c, 1)==1 && c != 'q' );
  return 0;
}

/* Step 1
 *   > read() and STD_FILENO come from <unistd.h>
 *   > We ask read() to read 1 byte from standard input into variable c.
 *   > Read returns the number of bytes that it read and returns 0 at the end
 *     of a file.
 *    
 * Step 2
 *   > when you run program terminal gets hooked up to standard input
 *   > keyboard input gets read into the c variable.
 *     - By default key input is only sent when you press enter
 *     - caninical or cooked mode
 *   > Raw Mode
 *   > raw mode is achieced by turning of many terminal flags
 *   
 * Step 3
 *   > 
 *
 *
 *
 *
 **/
