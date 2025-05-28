#include <error.h>
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