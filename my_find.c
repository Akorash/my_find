// Includes from getopt (mycommand) example
#include <getopt.h>
#include <assert.h>

// Includes from fork exampe
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>

// Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] …[filenameN]

// Accepted args: <searchpath> and <filename1 .. N>
// Variable n. of filenames to look for
// Options -R and -i can be placed anywhere in the args list

int main(int argc, char *argv[])
{
   // What are my arguments, parsing
   // Switch case
   // If only one argument, dont fork


}