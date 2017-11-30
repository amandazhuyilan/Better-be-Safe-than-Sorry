#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

/*
 *   print out string with a '--ECHO: ' prefix
 */
void echo(char *s, unsigned int l)
{
   unsigned char len = (unsigned char) l;
   char buf[512] = "--ECHO: ";

   strcat(buf, s);

   if (len >= 128) {
      fprintf(stderr, "argument too long!\n");
      exit(1);
   }
   else
      fprintf(stdout, "%s\n", buf);
}

/* 
 *   simple echo service that prints out its first argument
 */
int main(int argc, char **argv)
{
   /* check arguments */
   if (argc != 2) {
      fprintf(stderr, "please provide one argument to echo\n");
      return 1;
   }

   /* call the echo service */
   echo(argv[1], strlen(argv[1]));

   return 0;
}

//From course. Need to modify.
