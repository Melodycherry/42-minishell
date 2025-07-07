/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct_general.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:37:14 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 22:22:01 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_GENERAL_H
# define MS_STRUCT_GENERAL_H

# include "ms_type.h"

typedef struct s_cmd
{
	char	*line;
	char	**envp_copy;
	char	**envp_exp;
}	t_cmd;

typedef struct s_lexer
{
	int	single_quote;
	int	double_quote;
	int	space;
}	t_lexer;

typedef struct s_builtin
{
	t_bool	is_echo_n;
}	t_builtin;

typedef struct s_executor
{
	char			**av;
	char			**paths;
	char			**pipe_av;
	char			**redir_av;
	char			*redir_file;
	int				end;
	int				start;
	int				nb_pipe;
	int				nb_redir;
	int				nb_heredoc;
	int				nb_redir_wip;
	int				index_file_heredoc;
	t_bool			is_forked;
	t_bool			is_redir_beg;
	t_token_type	redir_type;
}	t_executor;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*var_value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tlist
{
	int		token_cnt;
	t_token	*head;
}	t_tlist;

typedef struct s_fd
{
	int	fd_pipe[2];
	int	prev_fd;
	int	saved_stdin;
	int	saved_stdout;
	int	fd_heredoc;
}	t_fd;

typedef struct s_shell
{
	t_bool		syntax_error;
	t_tlist		tlist;
	t_cmd		cmd;
	t_lexer		lexer;
	t_builtin	builtin;
	t_executor	executor;
	t_fd		fd;
}	t_shell;

#endif
