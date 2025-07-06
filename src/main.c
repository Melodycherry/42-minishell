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

static void	parsing(t_shell *shell);
static void	edgecase(t_shell *shell);
static int	is_line_empty(char *line);
static void	handle_signal(t_shell *shell);

int		g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_all(&shell);
	cpy_envp(&shell, envp);
	parent_signal();
	while (1)
	{
		shell.cmd.line = readline(PROMPT);
		if (!shell.cmd.line)
		{
			printf("exit");
			break ;
		}
		handle_signal(&shell);
		if (*shell.cmd.line && !is_line_empty(shell.cmd.line))
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

void	parsing(t_shell *shell)
{
	char	*value;

	token_blank(shell);
	token_operator(shell, shell->tlist.head);
	token_typedef(shell->tlist.head);
	if (shell->tlist.token_cnt == 1)
		edgecase(shell);
	value = error_multiple_operator(shell->tlist.head, shell);
	if (error_multiple_operator(shell->tlist.head, shell))
		return (error_syntax_token(shell, value));
	shell->syntax_error = FALSE;
	handle_heredoc(shell);
	expansion(shell);
}

static void	edgecase(t_shell *shell)
{
	if (only_quote(shell->tlist.head, '"'))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"));
	}
	if (only_quote(shell->tlist.head, '\''))
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "command ' ' not found"));
	}
	if (strcmp(shell->tlist.head->value, ".") == 0)
	{
		set_exit_status_env(shell, 2);
		return (error_message(shell, ".: filename argument required"));
	}
	if (strcmp(shell->tlist.head->value, "..") == 0)
	{
		set_exit_status_env(shell, 127);
		return (error_message(shell, "..: command not found"));
	}
}
static void	handle_signal(t_shell *shell)
{
	if (g_exit_status == SIGINT)
		set_exit_status_env(shell, 130);
	g_exit_status = 0;
}
static int	is_line_empty(char *line) // test pour segfault, ok 
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}
// < MAkefile cat
// echo > out.txt blabla
