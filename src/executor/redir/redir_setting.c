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

static void	cleanup_redirections(t_shell *shell);

void	set_redir_count(t_shell *shell, char **av)
{
	int		i;

	i = 0;
	shell->executor.nb_redir = 0;
	shell->executor.nb_redir_wip = 0;
	while (av && av[i])
	{
		if (is_redir(av[i]))
			shell->executor.nb_redir++;
		i++;
	}
	if (shell->executor.nb_redir > 0)
	{
		while (shell->executor.nb_redir_wip < shell->executor.nb_redir)
		{
			shell->executor.nb_redir_wip++;
			free_tab(&shell->executor.redir_av);
			set_redir_file_type_av(shell, av);
			redir_handle(shell);
		}
	}
	else
		cleanup_redirections(shell);
}

static void	cleanup_redirections(t_shell *shell)
{
	free_ptr((void **)&shell->executor.redir_file);
	shell->executor.redir_file = NULL;
	shell->executor.redir_type = 0;
	free_tab(&shell->executor.redir_av);
}

void	set_redir_file_type_av(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	set_redir_file(shell, av, &i);
	if (av[i + 1] == NULL)
	{
		ft_putendl_fd("Syntax error: expected file after redirection\n",
			STDERR_FILENO);
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
		free_tab(&shell->executor.redir_av);
		return ;
	}
	free_ptr((void **)&shell->executor.redir_file);
	shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
	if (!shell->executor.redir_file)
		unfructuous_malloc(shell);
	set_redir_type(shell, av[i]);
	free_tab(&shell->executor.redir_av);
	shell->executor.redir_av = set_redir_av(shell, av);
}

void	set_redir_file(t_shell *shell, char **av, int *i)
{
	int	count;

	count = 0;
	*i = 0;
	while (av[*i])
	{
		if (is_redir(av[*i]) == TRUE)
			count++;
		if (count == shell->executor.nb_redir_wip)
			break ;
		(*i)++;
	}
}

char	**set_redir_av(t_shell *shell, char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (av[i] && !is_redir(av[i]))
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		unfructuous_malloc(shell);
	i = 0;
	while (av[i] && !is_redir(av[i]))
	{
		new_tab[i] = ft_strdup(av[i]);
		if (!new_tab[i])
			free_mid_tab(shell, &new_tab, i);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
