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

/* fonction qui va compter le nb de redirection */
/*************** marche dans cet etat **************/
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
	{
		free_ptr((void **)&shell->executor.redir_file);
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
		free_tab(&shell->executor.redir_av);
	}
}

void	set_redir_file_type_av(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	set_redir_file(shell, av, &i);
	if (av[i + 1] == NULL)
	{
		fprintf(stderr, "Syntax error: expected file after redirection\n"); //TODO: gestion d erreur a refaire
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
		free_tab(&shell->executor.redir_av);
		return ;
	}
	free_ptr((void **)&shell->executor.redir_file);
	shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
	// if(!shell->executor.redir_file)
	// 	return //TODO: gestion erreur malloc pourri FOUT LA MERDE
	set_redir_type(shell, av[i]);
	free_tab(&shell->executor.redir_av);
	shell->executor.redir_av = set_redir_av(av);
}

void	set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0)
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, ">>") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
}

/* fonction qui va set le fichier juste apres la redir */
/*************** marche dans cet etat **************/
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

// petite correction ? ok now ? 
char	**set_redir_av(char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (av[i] && !is_redir(av[i]))
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (NULL); //TODO: sortie malloc pourri
	i = 0;
	while (av[i] && !is_redir(av[i]))
	{
		new_tab[i] = ft_strdup(av[i]);
		if (!new_tab[i])
			free_mid_tab(&new_tab, i);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
