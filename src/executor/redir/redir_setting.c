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
	printf("nb redir : %d\n", shell->executor.nb_redir);
	if (shell->executor.nb_redir > 0)
	{
		while (shell->executor.nb_redir_wip < shell->executor.nb_redir)
		{
			shell->executor.nb_redir_wip++;
			free_tab(&shell->executor.redir_av);
			set_redir_file_type_av(shell, av);
			puts("1");
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
	int		j;

	i = 0;
	j = 0;
	while (av[i] && !is_redir(av[i]))
	{
		i++;
		j++;
	}
	if (is_redir(av[i]) && av[i + 2])
		i += 2;
	while (av[i] && !is_redir(av[i]))
	{
		i++;
		j++;
	}
	new_tab = malloc(sizeof(char *) * (j + 1));
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
	if (is_redir(av[i]) && av[i + 2])
		i += 2;
	j = i - 2;
	while (av[i] && !is_redir(av[i]))
	{
		new_tab[j] = ft_strjoin_free(new_tab[j], av[i]);
		if (!new_tab[j])
			free_mid_tab(shell, &new_tab, j);
		if (av[i + 1])
		{
			new_tab[j] = ft_strjoin_free(new_tab[j], " ");
				if (!new_tab[j])
			free_mid_tab(shell, &new_tab, j);
		}
		i++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}

// char	**set_redir_av(t_shell *shell, char **av)
// {
// 	char	**new_tab;
// 	int		i;

// 	i = 0;
// 	while (av[i] && !is_redir(av[i]))
// 		i++;
// 	new_tab = malloc(sizeof(char *) * (i + 1));
// 	if (!new_tab)
// 		unfructuous_malloc(shell);
// 	i = 0;
// 	while (av[i] && !is_redir(av[i]))
// 	{
// 		new_tab[i] = ft_strdup(av[i]);
// 		if (!new_tab[i])
// 			free_mid_tab(shell, &new_tab, i);
// 		i++;
// 	}
// 	new_tab[i] = NULL;
// 	return (new_tab);
// }


	// printf("av 0 = %s\n", av[0]);
	// if (is_redir(av[0]))
	// {
	// 	ft_putendl_fd("Syntax error: expected command before redirection\n",
	// 		STDERR_FILENO);
	// 	shell->executor.redir_file = NULL;
	// 	shell->executor.redir_type = 0;
	// 	free_tab(&shell->executor.redir_av);
	// 	return ;
	// }