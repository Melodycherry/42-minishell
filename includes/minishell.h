/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlichten <hlichten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:37:01 by hlichten          #+#    #+#             */
/*   Updated: 2025/07/07 20:37:03 by hlichten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//readline
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
//le reste
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# include "ft_printf.h"
# include "libft.h"
# include "ms_struct_general.h"
# include "ms_function.h"
# include "ms_type.h"

extern int	g_exit_status;

# define PROMPT "Les codeuses du dimanche : "

#endif
