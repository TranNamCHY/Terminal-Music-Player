/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <filesystem>
#include "HomeView.h"
#include <termios.h>
#include <unistd.h>
#include "SkeletonController.h"
using namespace  std;
void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw); // Get current terminal settings

    raw.c_lflag &= ~(ECHO | ICANON); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply settings
}

void disableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);

    raw.c_lflag |= (ECHO | ICANON); // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Apply settings
}
int main()
{
    SkeletonController* test = SkeletonController::getInstance();
    test->run();
    //while(true);
}