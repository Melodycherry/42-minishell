/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:12 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:34:14 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_syntax_export(char *line)
{
	ft_putstr_fd("bash: export: «", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("»: not a valid identifier\n", STDERR_FILENO);
}

void	error_syntax_unset(char *line)
{
	ft_putstr_fd("bash: unset: «", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("»: not a valid identifier\n", STDERR_FILENO);
}

void	error_message(t_shell *shell, char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	free_and_reset(shell);
	shell->syntax_error = TRUE;
	return ;
}

void	error_syntax_token(t_shell *shell, char *value)
{
	ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(value, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free_and_reset(shell);
	shell->syntax_error = TRUE;
	return ;
}
