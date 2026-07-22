#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int
echo (char array[], int size)
{
  if (size == 4)
    {
      printf ("\n");
      return 0;
    }

  int j = 0;
  char new_array[size - 4];

  for (int i = 5; i < size; i++)
    {
      new_array[j++] = array[i];
    }

  new_array[j] = '\0';

  write (1, new_array, strlen (new_array));
  printf ("\n");

  return 0;
}



int
main (int argc, char *argv[])
{
  int buf_size = 100;
  char bufold[buf_size];
  char buf[buf_size];

  while (1)
    {
      printf ("Simple Shell: Enter your command $");
      fgets (bufold, buf_size, stdin);
      bufold[strlen (bufold) - 1] = 0;

      if (strlen (bufold) == 0)
	continue;


      int i = 0;
      int j = 0;
      while (i < buf_size)
	{
	  // to kill only the white spaces before first character and replace all white spaces after the first chaeacter with one white space 

	  if (bufold[i] == ' ')
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      while (bufold[i] != '\0')
		{
		  buf[j] = bufold[i];
		  i++;
		  j++;

		  if (bufold[i] == ' ')
		    {
		      buf[j] = ' ';
		      i++;
		      j++;
		    }
		  while (bufold[i] == ' ')
		    {
		      i++;
		    }

		}

	      break;


	    }
	}


  if (j > 0 && buf[j-1] == ' ')
	buf[j-1] = '\0';
	else 	buf[j] = '\0';


	
  if ((buf[0] == 'e' && buf[1] == 'c' && buf[2] == 'h'
	   && buf[3] == 'o' && buf[4] == ' ') || (buf[0] == 'e'
						  && buf[1] == 'c'
						  && buf[2] == 'h'
						  && buf[3] == 'o'
						  && strlen (buf) == 4))
	echo (buf, j);


	else if (strlen(buf) == 4 && buf[0] == 'e' && buf[1] == 'x'
		 && buf[2] == 'i' && buf[3] == 't') {
	    printf("Good Bye\n");
	    exit(0);


	} else
	    printf("Invalid command\n");

    }
    return 0;

}
