/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      LES CODEUSES DU DIMANCHE                                             */
/*      FONT UN MINISHELL                                                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "minishell.h"

// ATTENTION SEGFAULT avec unexpected token qd on free. 
// si on free pas y'a zero leaks mais a rechecker si ca leak ailleurs ?? 
void	parsing(t_shell *shell)
{

	token_blank(shell);
	token_operator(shell, shell->tlist.head);
	token_typedef(shell->tlist.head);
	if (is_token_error(shell->tlist.head, shell) == TRUE)
	{
		ft_putendl_fd("Syntax error near unexpected token", STDERR_FILENO);
		//free_and_reset(shell); c'est ca qui pose pb , mais du coup il faut pas free
		return;
	}
	handle_heredoc(shell);
	expansion(shell);

	// test impression
	// print_token(shell->tlist.head, printf); // pour cette shit d expansion
	// print_token2(shell->tlist.head, printf);
	// print_token3(shell->tlist.head, printf);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_all(&shell);
	cpy_envp(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.cmd.line = readline(PROMPT);
		if (!shell.cmd.line)
		{
			printf("exit");
			break ;
		}
		if (*shell.cmd.line)
		{
			add_history(shell.cmd.line);
			parsing(&shell);
			execution(&shell);
			unlink_file(&shell);
			free_and_reset(&shell);
		}
	}
	free_all(&shell);
	return (0);
}
