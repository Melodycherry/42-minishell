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
	if (shell->tlist.token_cnt == 1 && is_only_quotes(shell->tlist.head)) // faire plus de test avec cette hsitoire
		return (error_empty_token(shell));
	value = error_multiple_operator(shell->tlist.head, shell);
	if (error_multiple_operator(shell->tlist.head, shell))
		return (error_syntax_token(shell, value));
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

// "" -> en cours, a tester a 42
// cat << eof << 
// cat | cat | ls
//?