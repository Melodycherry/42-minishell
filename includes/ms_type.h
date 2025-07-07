/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:37:18 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:20 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPE_H
# define MS_TYPE_H

typedef enum e_token_type
{
	T_UNKNOWN,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_EOF,
	T_EOF_Q,
	T_VAR
}	t_token_type;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_envp
{
	NON_EXISTANT,
	TO_EXPORT,
	TO_ENV,
	TO_BOTH
}	t_envp;

#endif