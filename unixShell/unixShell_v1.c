/*https://github.com/brenns10/lsh/tree/407938170e8b40d231781576e05282a41634848c
 * Initialize: Read and executes its config files. These change aspects of shell
 *             behavior.
 *
 * Interpret: Reads commands from stdin and executes them
 * 
 * Terminate: Executes shutdown commands, frees up memory, and termi
 *
 ***/

/*
 * Basic loop of shell
 *   > Read: command from standard input
 *   > Parse: Seperate the command string into a program and arguments
 *   > Execute: Run the parsed command
 ***/


//#include <stdio.h>
/*
#define LSH_RL_BUFSIZE 1024

char *shell_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char)*bufsize);
  int c;

  if (!buffer) {
	fprintf(stderr, "shell: allocation error\n");
	exit(EXIT_FAILURE);
  }

while (1) {
  // Read a character
  c = getchar();
 
  // If we hit EOF, replace it with a null character and return
  if (c==EOF || c == '\n')
    { 
	buffer[position]='\0';
        return buffer;
     } 
  else 
     {
	buffer[position] = c;
     }
  position++;

  // If we have exceeded the buffer, reallocate. 
  if (position >= bufsize)
    {
	bufsize += LSH_RL_BUFSIZE;
	buffer = realloc(buffer, bufsize);
	if(!buffer)
	  {
	    fprintf(stderr, "shell: allocation error\n");
	    exit(EXIT_FAILURE);
	  }
    }
   }
}
**/

#include <sys/wait.h>
  // waitpid() and associated macros
#include <unistd.h>
  // chdir()
  // fork()
  // exec()
  // pid_t
 
#include <stdlib.h>
  // malloc
  // realloc
  // free()
  // exit()
  // execvp
  // EXIT_SUCCESS, EXIT_FAILURE
 
#include <stdio.h>
  // fprintf()
  // printf()
  // stderr()
  // getchar()
  // perror()
 
#include <string.h>
  // strcmp()
  // strok()


char *shell_read_line_v2(void)
  {
    char *line=NULL;
    ssize_t bufsize=0; // have getline() allocate a buffer for us
    getline(&line, &bufsize, stdin);
    return line;
  }

void shell_loop(void)
{
  char *line;
  char **args;
  int status;

  do 
  {
    printf("> ");
    line = shell_read_line();
    args = shell_split_line(line);
    status = shell_execute(args);

    free(line);
    free(args);
  }
  while (status);
}
/*
 * # Reading a line from stdin
 *   hard to do because you must allocate
 *   a block to size beforhand.
 **/
 
/*
 * Parsing
 * Need to tokenize the string using whitespace as delimiters
 * Use classic library strok
 * */

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **shell_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize *sizeof(char*));
  char *token;

  if (!tokens) 
    {
	fprintf(stderr, "shell: allocation error\n");
	exit(EXIT_FAILURE);
     }
 
  token = strok(line, LSH_TOK_DELIM);
  while (token != NULL)	
    {
	takens[position] = token;
	position++;
    if (position >= bufsize)
      {
	bufsize += LSH_TOK_BUFSIZE;
        tokens = realloc(tokens, bufsize * sizeof(char*));
	if (!tokens)
	  {
	    fprintf(stderr, "shell: allocation error\n")
	    exit(EXIT_FAILURE)
	  }
      }
      token = strok(NULL, LSH_TOK_DELIM);
      return tokens;
  }
}

/*
 *
 * Starting Processes
 * two ways
 * being Init
 * fork() system call
 *
 * exec() replaces the current running program
 * first existing process is forked into two seperate processes
 * next exec() is used by the child process to replace the old running one
 * using wait() the parent process can keep tabs on its children
 * */



int shell_launch(char **args)

{
  pid_t pid, wpid;
  int status;
 
  pid = fork();
  if (pid==0)
    {
      //Child Process
      if (execvp(args[0], args)==-1)
	{ 
	  perror("shell");
	}
	exit(EXIT_FAILURE);
	}
      else if (pid<0)
	{
          // Error forking
	  perror("shell");
	}
      else
	{
	  // Parent Process
	  do
	    { 
	      wpid = waitpid(pid, &status, WUNTRACED);
	    }
	  while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
  return 1;
 }

/*
 * Function Declarations for buitlin shell commands
 * */

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

/* 
 * List of builtin commands followed by thier correponding functions
 * */

char *builtin_str[] =
  {
    "cd",
    "help",
    "exit"
  };

int (*builtin_func[]) (char**) =
  {
    &shell_cd,
    &shell_help,
    &shell_exit
  }
int shell_num_builtins()
  {
    return sizeof(builtin_str) / sizeof(char *);
  }
/* 
 * Builtin function implementations
 * */

int shell_cd(char **args)
{
  if (args[1] == NULL)
    {
	fprintf(stderr, "shell: expected argument to \"cd\"|n");
    }
  else
    {
      if (chdir(args[1]) !=0)
	{
	   perror("shell");
	}
     }
     return 1;
}

int shell_help(char **args)
{
  int i;
     printf("Ghouls SHELL \n");
     printf("Type program names and arguements, and hit enter.\n");
     printf("THe following are built in: \n");

     for (i=0; i< shell_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
     }
     printf("Use the man command for information on others programs.\n");
     return 1;
     }

int shell_exit(char **args)
{
  return 0;
}

int shell_execute(char **args)
{
  int i;
  if (args[0]==NULL){
    // An empty command was entered.
    return 1;
   }
   for (i=0; i<shell_num_builtins();i++){
      if (strcmp(args[0], builtin_str[i]) ==0 ){
	return (*builtin_func[i])(args);
      }
    }
   return shell_launch(args);
}

	

	

int main(int argc, char **argv)
  {
	// Load config files, if any
	
	// Run command loop
	shell_loop();

	// Perform any shutdown/cleanup
	
	return EXIT_SUCCESS;
  }
	
