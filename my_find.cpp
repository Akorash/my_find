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
   bool caseSensitive = false;
   bool recursive = false;
   
   int c;
   while ((c = getopt(argc, argv, "iR")) != EOF)
   {
        switch (c)
        {
         case '?':
            fprintf(stderr, "unknown opt\n");
            break;
         case 'i':
            fprintf(stderr, "Case sensitive requested\n");
            !caseSensitive;
            break;
         case 'R':
            fprintf(stderr, "Recursive search requested\n");
            !recursive;
            break;
         default:
            fprintf(stderr, "Default\n");
            return 0;
        }
   }

   char *filepath = argv[optind];
   optind++;
   fprintf(stderr, "filepath: %s\n", filepath);

   for(int i = 0; i < argc - optind; i++)
   {
      fprintf(stderr,"files: %s\n",argv[optind + i]);
   }
   

   // If only one argument, dont fork
   // iterating through directories


}