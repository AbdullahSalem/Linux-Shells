#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

extern char **environ;
char local_variable_table[100][100];
int local_variable_count = 0;

int store_local_variable(char command[], int command_length)
{

  for (int i = 0; i < command_length; i++)
  {
    local_variable_table[local_variable_count][i] = command[i];

  }
local_variable_table[local_variable_count][command_length] = '\0';
local_variable_count++;
return 0;

}



int store_environment_variable(char command[], int command_length, int equal_sign_position)
{
  char environment_variable_name[100];
  char environment_variable_value[100];
  int k = 0;
  for (int i = 7; i < equal_sign_position; i++)
  {

    environment_variable_name[k] = command[i];
    k++;
  }
environment_variable_name[k] = '\0';

int m = 0;

for (int i = equal_sign_position + 1; i < command_length; i++)
{

  environment_variable_value[m] = command[i];
  m++;
}
environment_variable_value[m] = '\0';

setenv(environment_variable_name, environment_variable_value, 1);
return 0;

}



char *expand_variable_reference(char command[], int command_length)
{
  int i = 0;
  int dollar_sign_position = -1;
  char variable_name[100];
  for (i = 0; i < command_length; i++)
  {
    if (command[i] == '$')
    {
      dollar_sign_position = i;
      break;
    }
}

int k = 0;
if (dollar_sign_position == -1)
return command;

for (i = dollar_sign_position + 1; i < command_length; i++)
{
  if (command[i] == ' ')
  break;
  variable_name[k] = command[i];
  k++;
}
variable_name[k] = '\0';
int variable_name_length = strlen(variable_name);
int variable_position = -1;
k = 0;
for (i = 0; i < local_variable_count; i++)
{
  k = 0;
  for (int j = 0; j < variable_name_length; j++)
  {
    if (local_variable_table[i][j] != variable_name[j])
    {
      break;
    }

  k++;

  if (k == variable_name_length && local_variable_table[i][variable_name_length] == '=')
  {
    variable_position = i;
    goto out4;
  }
}
}


out4:

char *variable_value;

if (variable_position == -1)
{
  variable_value = getenv(variable_name);
  if (variable_value == NULL)
  return command;
} else
{
variable_value = strchr(local_variable_table[variable_position], '=');
}

int variable_value_length = strlen(variable_value);

int remaining_command_length = strlen(command) - (dollar_sign_position + 1 + variable_name_length);

char remaining_command[remaining_command_length + 1];
int r = dollar_sign_position + variable_name_length + 1;
for (int i = 0; i < remaining_command_length; i++)
{
  remaining_command[i] = command[r];
  r++;
}
remaining_command[remaining_command_length] = '\0';

int m = dollar_sign_position;
// i = 1 to get the second character after = (the real first character in the value array)
int s;
if (variable_position == -1)
s = 0;
else if (variable_position != -1)
s = 1;

for (int i = s; i < variable_value_length; i++)
{
  command[m] = variable_value[i];
  m++;
}

for (int i = 0; i < remaining_command_length; i++)
{
  command[m] = remaining_command[i];
  m++;
}
command[m] = '\0';

return command;
}



int echo(char command[], int command_length)
{
  if (command_length == 4)
  {
    printf("\n");
    return 0;
  }

int j = 0;
char echo_text[command_length - 4];

for (int i = 5; i < command_length; i++)
{
  echo_text[j++] = command[i];
}

echo_text[j] = '\0';

write(1, echo_text, strlen(echo_text));
printf("\n");

return 0;
}




int cd(char command[], int command_length)
{
  if (command_length == 2 || (command_length == 3 && command[2] == ' '))
  {
    chdir("/home");
    return 0;
  }

int j = 0;
char target_directory[command_length - 3];

for (int i = 3; i < command_length; i++)
{
  target_directory[j++] = command[i];
}

target_directory[j] = '\0';

if (chdir(target_directory) < 0)
{
  perror("cd");
  return 0;
}
return 0;
}



int pwd()
{
  int directory_buffer_size = 1;
  while (1)
  {

    char current_directory [directory_buffer_size];
    char *cwd_result = getcwd(current_directory, directory_buffer_size);

    if (cwd_result == NULL)
    directory_buffer_size++;

    else
    {
      write(1, current_directory, strlen(current_directory));
      printf("\n");
      break;
    }
}
return 0;
}



int execution(char command[], int command_length)
{

  int path1_size = 15 + command_length + 1;
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

  int path2_size = 9 + command_length + 1;
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

  int path3_size = 5 + command_length + 1;
  char path3[path3_size];
  path3[0] = '/';
  path3[1] = 'b';
  path3[2] = 'i';
  path3[3] = 'n';
  path3[4] = '/';

  int j = 0;
  for (int i = 15; i < path1_size; i++)
  {

    path1[i] = command[j];
    j++;
  }


path1[j + 15] = '\0';
j = 0;
for (int i = 9; i < path2_size; i++)
{

  path2[i] = command[j];
  j++;
}
path2[j + 9] = '\0';
j = 0;
for (int i = 5; i < path3_size; i++)
{

  path3[i] = command[j];
  j++;
}
path3[j + 5] = '\0';



char *argv1[] = { path1, NULL };
// char *envp[] = { NULL };


pid_t pid = fork();
if (pid > 0)
{
  int status;
  wait(&status);
  WEXITSTATUS(status);


} else if (pid == 0)
{
if (execve(path1, argv1, environ) < 0)
{
  char *argv2[] = { path2, NULL };
  if (execve(path2, argv2, environ) < 0)
  {
    char *argv3[] = { path3, NULL };
    if (execve(path3, argv3, environ))
    {
      printf("Invalid command\n");
    }
}

}
exit(1);
} else
{
printf("Process Failed");
}

return 0;

}



int main(int argc, char *argv[])
{
  int input_buffer_size = 100;
  char raw_user_input[input_buffer_size];
  char normalized_command[input_buffer_size];

  while (1)
  {
    out3:
    printf("Simple Shell: Enter your command $");
    fgets(raw_user_input, input_buffer_size, stdin);
    raw_user_input[strlen(raw_user_input) - 1] = 0;

    if (strlen(raw_user_input) == 0)
    continue;

    int i = 0;
    int j = 0;
    while (i < input_buffer_size)
    {
      // to kill only the white spaces before first character and replace all white spaces after the first chaeacter with one white space

      if (raw_user_input[i] == ' ')
      {
        i++;
        continue;
      } else
      {
      while (raw_user_input[i] != '\0')
      {
        normalized_command[j] = raw_user_input[i];
        i++;
        j++;

        if (raw_user_input[i] == ' ')
        {
          normalized_command[j] = ' ';
          i++;
          j++;
        }
      while (raw_user_input[i] == ' ')
      {
        i++;
      }

  }

break;


}
}

if (normalized_command[j - 1] == ' ')
normalized_command[j - 1] = '\0';
else
normalized_command[j] = '\0';

// j => normalized_command size
expand_variable_reference(normalized_command, j);
j = strlen(normalized_command);
int equal_sign_position = 0;

if ((normalized_command[0] == 'e' && normalized_command[1] == 'c' && normalized_command[2] == 'h'
&& normalized_command[3] == 'o' && normalized_command[4] == ' ') || (normalized_command[0] == 'e'
&& normalized_command[1] == 'c'
&& normalized_command[2] == 'h'
&& normalized_command[3] == 'o'
&& strlen(normalized_command) == 4))
{
  echo(normalized_command, j);
  continue;
} else
{

for (int i = 0; i < j && normalized_command[i] != '\0'; i++)
{

  if (normalized_command[i] == '=' && normalized_command[i + 1] != ' '
  && normalized_command[i - 1] != ' ')
  {
    equal_sign_position = i;


    for (int i = 0; i < equal_sign_position; i++)
    {
      if (normalized_command[i] == ' ')
      goto out1;
    }

  for (int i = equal_sign_position;
  i < j && normalized_command[equal_sign_position + 1] != '"'
  && normalized_command[j - 1] != '"'; i++)
  {
    if (normalized_command[i] == ' ')
    goto out1;
  }

store_local_variable(normalized_command, j);
goto out3;



}
}


}

out1:

if ((strlen(normalized_command) == 4 && normalized_command[0] == 'e' && normalized_command[1] == 'x'
&& normalized_command[2] == 'i' && normalized_command[3] == 't') || (strlen(normalized_command) == 5
&& normalized_command[0] == 'e'
&& normalized_command[1] == 'x'
&& normalized_command[2] == 'i'
&& normalized_command[3] == 't'
&& normalized_command[4] == ' '))
{
  printf("Good Bye\n");
  exit(0);


} else if ((strlen(normalized_command) == 3 && normalized_command[0] == 'p' && normalized_command[1] == 'w'
&& normalized_command[2] == 'd') || (strlen(normalized_command) == 4 && normalized_command[0] == 'p'
&& normalized_command[1] == 'w' && normalized_command[2] == 'd'
&& normalized_command[3] == ' '))
{
  pwd();
}

else if ((normalized_command[0] == 'c' && normalized_command[1] == 'd' && normalized_command[2] == ' ')
|| (normalized_command[0] == 'c' && normalized_command[1] == 'd' && strlen(normalized_command) == 2))
{
  cd(normalized_command, j);
}


else if (normalized_command[0] == 'e' && normalized_command[1] == 'x' && normalized_command[2] == 'p'
&& normalized_command[3] == 'o' && normalized_command[4] == 'r' && normalized_command[5] == 't'
&& normalized_command[6] == ' ')
{
  for (int i = 7; i < j && normalized_command[i] != '\0'; i++)
  {

    if (normalized_command[i] == '=' && normalized_command[i + 1] != ' '
    && normalized_command[i - 1] != ' ')
    {
      equal_sign_position = i;


      for (int i = 7; i < equal_sign_position; i++)
      {
        if (normalized_command[i] == ' ')
        goto out2;
      }

    for (int i = equal_sign_position;
    i < j && normalized_command[equal_sign_position + 1] != '"'
    && normalized_command[j - 1] != '"'; i++)
    {
      if (normalized_command[i] == ' ')
      goto out2;
    }

  store_environment_variable(normalized_command, j, equal_sign_position);
  goto out3;
}
}
}

else
out2:
execution(normalized_command, strlen(normalized_command));
}
return 0;
}
