//#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int fd_pipe[2];
	
	pid_t pid_child_Melo;
	pid_t pid_child_IJ;
	int stat_loc_Melo;
	int stat_loc_IJ;

	if (pipe(fd_pipe) == -1)
		perror("Error ");

	pid_child_Melo = fork();
	pid_child_IJ = fork();

	if (pid_child_IJ == -1 || pid_child_Melo == -1)
		perror("Error ");
	printf("Child Melo %d\n", pid_child_Melo);
	printf("Child IJ %d\n", pid_child_IJ);
	
	if (pid_child_Melo == 0)
	{
		printf("Child Melo\n");
		sleep(30);
		exit(EXIT_FAILURE);
	}

	if (pid_child_IJ == 0)
	{
		printf("Child IJ\n");
		sleep(30);
		exit(EXIT_FAILURE);
	}
	if (waitpid(pid_child_Melo, &stat_loc_Melo, 0) == -1)
		perror("Error ");
	if (waitpid(pid_child_IJ, &stat_loc_IJ, 0) == -1)
		perror("Error ");
	printf("exit status Melo %d\n", stat_loc_Melo);
	printf("exit status IJ %d\n", stat_loc_IJ);
}











// exemple quenpou
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 20

void parse_command(char *input, char **argv)
{
	int i = 0;
	char *token = strtok(input, " ");
	while (token && i < MAX_ARGS - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}

int main(void)
{
	char input[256];
	char *cmd1[MAX_ARGS], *cmd2[MAX_ARGS];

	while (1)
	{
		printf("mini-shell> ");
		if (!fgets(input, sizeof(input), stdin))
			break;

		input[strcspn(input, "\n")] = 0; // enlève le \n

		if (strcmp(input, "exit") == 0)
			break;

		// Vérifie s’il y a un pipe |
		char *pipe_pos = strchr(input, '|');
		if (pipe_pos)
		{
			*pipe_pos = 0; // coupe la chaîne en deux
			char *left = input;
			char *right = pipe_pos + 1;

			parse_command(left, cmd1);
			parse_command(right, cmd2);

			int fd[2];
			if (pipe(fd) == -1)
			{
				perror("pipe");
				continue;
			}

			pid_t pid1 = fork();
			if (pid1 == -1)
			{
				perror("fork 1");
				continue;
			}

			if (pid1 == 0)
			{
				// Enfant 1 (commande de gauche)
				close(fd[0]); // Ne lit pas
				dup2(fd[1], STDOUT_FILENO); // Redirige stdout vers l’écriture du pipe
				close(fd[1]);

				execvp(cmd1[0], cmd1);
				perror("execvp 1");
				exit(EXIT_FAILURE);
			}

			pid_t pid2 = fork();
			if (pid2 == -1)
			{
				perror("fork 2");
				continue;
			}

			if (pid2 == 0)
			{
				// Enfant 2 (commande de droite)
				close(fd[1]); // Ne veut pas écrire
				dup2(fd[0], STDIN_FILENO); // Redirige stdin vers la lecture du pipe
				close(fd[0]);

				execvp(cmd2[0], cmd2);
				perror("execvp 2");
				exit(EXIT_FAILURE);
			}

			// Parent : ferme le pipe et attend les deux
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
		else
		{
			// Pas de pipe : commande simple
			parse_command(input, cmd1);

			pid_t pid = fork();
			if (pid == -1)
			{
				perror("fork");
				continue;
			}

			if (pid == 0)
			{
				execvp(cmd1[0], cmd1);
				perror("execvp");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
	}

	return 0;
}
