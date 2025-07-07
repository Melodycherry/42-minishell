/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:57 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:35:43 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing(t_shell *shell);
static void	handle_signal(t_shell *shell);
static void	minishell_loop(t_shell *shell);

int		g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_all(&shell);
	cpy_envp(&shell, envp);
	parent_signal();
	minishell_loop(&shell);
	free_all(&shell);
	return (0);
}

static void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		shell->cmd.line = readline(PROMPT);
		if (!shell->cmd.line)
		{
			printf("exit");
			break ;
		}
		handle_signal(shell);
		if (*shell->cmd.line && !is_line_empty(shell->cmd.line))
		{
			add_history(shell->cmd.line);
			parsing(shell);
			if (shell->syntax_error == FALSE)
			{
				execution(shell);
				unlink_file(shell);
			}
			free_and_reset(shell);
		}
	}
}

void	parsing(t_shell *shell)
{
	char	*value;

	token_blank(shell);
	token_operator(shell, shell->tlist.head);
	token_typedef(shell->tlist.head);
	if (shell->tlist.token_cnt == 1)
		if (edgecase(shell) == TRUE)
			return ;
	value = error_multiple_operator(shell->tlist.head, shell);
	if (error_multiple_operator(shell->tlist.head, shell))
		return (error_syntax_token(shell, value));
	shell->syntax_error = FALSE;
	handle_heredoc(shell);
	expansion(shell);
}

static void	handle_signal(t_shell *shell)
{
	if (g_exit_status == SIGINT)
		set_exit_status_env(shell, 130);
	g_exit_status = 0;
}
