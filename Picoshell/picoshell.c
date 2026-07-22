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
cd (char array[], int size)
{
  if (size == 2 || (size == 3 && array[2] == ' '))
    {
      chdir ("/home");
      return 0;
    }


  int j = 0;
  char new_array[size - 3];

  for (int i = 3; i < size; i++)
    {
      new_array[j++] = array[i];
    }

  new_array[j] = '\0';

  if (chdir (new_array) < 0)
    {
      perror ("cd");
      return 0;
    }
  return 0;
}

int
pwd ()
{
  int bytes = 1;
  while (1)
    {

      char path[bytes];

      char *test = getcwd (path, bytes);

      if (test == NULL)
	bytes++;

      else
	{
	  write (1, path, strlen (path));
	  printf ("\n");
	  break;
	}
    }
  return 0;
}


int
execution (char buf[], int size)
{

  int path1_size = 15 + size +1;
  char path1[path1_size];
  path1[0] = '/';
  path1[1] = 'u';
  path1[2] = 's';
  path1[3] = 'r';
  path1[4] = '/';
  path1[5] = 'l';
  path1[6] = 'o';
  path1[7] = 'c';
  path1[8] = 'a';
  path1[9] = 'l';
  path1[10] = '/';
  path1[11] = 'b';
  path1[12] = 'i';
  path1[13] = 'n';
  path1[14] = '/';

  int path2_size = 9 + size +1;
  char path2[path2_size];
  path2[0] = '/';
  path2[1] = 'u';
  path2[2] = 's';
  path2[3] = 'r';
  path2[4] = '/';
  path2[5] = 'b';
  path2[6] = 'i';
  path2[7] = 'n';
  path2[8] = '/';

  int path3_size = 5 + size +1;
  char path3[path3_size];
  path3[0] = '/';
  path3[1] = 'b';
  path3[2] = 'i';
  path3[3] = 'n';
  path3[4] = '/';


  int j = 0;
  for (int i = 15; i < path1_size; i++)
    {

      path1[i] = buf[j];
      j++;
    }
    

  path1[j+15] = '\0';
  j = 0;
  for (int i = 9; i < path2_size; i++)
    {

      path2[i] = buf[j];
      j++;
    }
  path2[j+9] = '\0';
  j = 0;
  for (int i = 5; i < path3_size; i++)
    {

      path3[i] = buf[j];
      j++;
    }
  path3[j+5] = '\0';



  char *argv1[] = { path1, NULL };
  char *envp[] = { NULL };


  pid_t pid = fork ();
  if (pid > 0)
    {
      int status;
      wait (&status);
      WEXITSTATUS (status);


    }
  else if (pid == 0)
    {
      if (execve (path1, argv1, envp) < 0)
	{
	  char *argv2[] = { path2, NULL };
	  if (execve (path2, argv2, envp) < 0)
	    {
	      char *argv3[] = { path3, NULL };
	      if (execve (path3, argv3, envp))
		{
		  printf ("Invalid command\n");
		}
	    }


	}
      exit (1);
    }
  else
    {
      printf ("Process Failed");
    }






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

      else if ((strlen (buf) == 4 && buf[0] == 'e' && buf[1] == 'x'
		&& buf[2] == 'i' && buf[3] == 't') || (strlen (buf) == 5
						       && buf[0] == 'e'
						       && buf[1] == 'x'
						       && buf[2] == 'i'
						       && buf[3] == 't'
						       && buf[4] == ' '))
	{
	  printf ("Good Bye\n");
	  exit (0);


	}
      else if ((strlen (buf) == 3 && buf[0] == 'p' && buf[1] == 'w'
		&& buf[2] == 'd') || (strlen (buf) == 4 && buf[0] == 'p'
				      && buf[1] == 'w' && buf[2] == 'd'
				      && buf[3] == ' '))
	{
	  pwd ();


	}

      else if ((buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
	       || (buf[0] == 'c' && buf[1] == 'd' && strlen (buf) == 2))
	{
	  cd (buf, j);


	}


      else
	execution (buf, strlen(buf));


    }

  return 0;

}
