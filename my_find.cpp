#include <string>

// Includes from getopt (mycommand) example
#include <getopt.h>
#include <assert.h>

// Includes from fork exampe
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//include from dir example
#include <dirent.h>
#include <errno.h>

// Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] …[filenameN]

// Accepted args: <searchpath> and <filename1 .. N>
// Variable n. of filenames to look for

void search(bool caseSensitive, bool recursive, std::string path, std::string filename);

int main(int argc, char *argv[])
{
   bool caseSensitive = true;
   bool recursive = false;

   if( 1 > argc - (optind+ 1))
   {
      fprintf(stderr, "No file and/or path given\nUsage: ./myfind [-R] [-i] searchpath filename1 [filename2] …[filenameN]\n");
      return -1;
   }
   
   int c;
   while ((c = getopt(argc, argv, "iR")) != EOF)
   {
        switch (c)
        {
         case '?':
            fprintf(stderr, "unknown opt\n");
            break;
         case 'i':
            fprintf(stderr, "Case insensitive requested\n");
            caseSensitive = false;
            break;
         case 'R':
            fprintf(stderr, "Recursive search requested\n");
            recursive = true;
            break;
         default:
            fprintf(stderr, "Default\n");
            return 0;
        }
   }

   char *filepath = argv[optind];
   optind++;
   fprintf(stderr, "filepath: %s\n", filepath);

   pid_t pid;
   for(int i = 0; i < argc - optind; i++)
   {
      switch(pid = fork())
      {
      case -1:
         fprintf(stderr, "Error in calling fork()\n"); // or perror("Failed to fork");
         return EXIT_FAILURE;
      case 0:
         search(caseSensitive, recursive, filepath, argv[optind + i]);
         break;
      default:
         fprintf(stderr,"files: %s\n",argv[optind + i]);
         continue;
      }
      break;
   }
}

void search(bool caseSensitive, bool recursive, std::string path, std::string filename)
{
   struct dirent *direntp;
   DIR *dirp;

   if ((dirp = opendir(path.c_str())) == NULL) 
   {
      perror("failed to open directory");
      return;
   }

   while ((direntp = readdir(dirp)) != NULL) //while valid dir is given it iterates through entries
   {
      if(!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..")) //prevents endless loop for next func
      {
         continue;
      }

      if(direntp->d_type == DT_DIR) //checks if curr entry is dir
      {
         if(recursive)
         {
            search(caseSensitive, recursive, path + "/" + direntp->d_name, filename); //search gets called recursively
         }
         continue;
      }

      if((!caseSensitive && !strcasecmp(direntp->d_name, filename.c_str()))
      || (caseSensitive && !strcmp(direntp->d_name, filename.c_str()))) //depending on if case sensitive was chosen or not -> strcmp or strcasecmp
      {
         char filepath[pathconf(".",_PC_PATH_MAX)];
         realpath((path + "/" + direntp->d_name).c_str(), filepath); //to get absolute path 
         fprintf(stdout, "%d: %s: %s\n", getpid(), filename.c_str(), filepath);
      }

   }

   while ((closedir(dirp) == -1) && (errno == EINTR))
      ;
}