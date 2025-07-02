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

void	parsing(t_shell *shell)
{
	char	*value;

	token_blank(shell);
	token_operator(shell, shell->tlist.head);
	token_typedef(shell->tlist.head);
	value = error_multiple_operator(shell->tlist.head, shell);
	if (error_multiple_operator(shell->tlist.head, shell))
	{
		ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		free_and_reset(shell);
		shell->syntax_error = TRUE;
		return ;
	}
	shell->syntax_error = FALSE;
	handle_heredoc(shell);
	expansion(shell);
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
			if (shell.syntax_error == FALSE)
			{
				execution(&shell);
				unlink_file(&shell);
			}
			free_and_reset(&shell);
		}
	}
	free_all(&shell);
	return (0);
}

// ""
// cat << eof << 
// cat | cat | ls
//?