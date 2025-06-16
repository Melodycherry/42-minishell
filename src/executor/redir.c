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


// redirection en cours merci de ne pas juger lololol :) 


/* va verifier si presence de redir, les faire fonctionner et executer*/
/******** tout fonctionne sauf l execution ********/
void	redir_handle(t_shell *shell, char **av)
{
	t_token_type type;
	redir_count_set(shell, av);

	type = shell->executor.redir_type;
	if (shell->executor.nb_redir > 0)
	{
		if (type == T_REDIR_IN)
			handle_redir_in(shell->executor.redir_file);
		if (type == T_REDIR_OUT)
			handle_redir_out(shell->executor.redir_file);
		if (type == T_REDIR_APPEND)
			handle_redir_append(shell->executor.redir_file);
	}
}

/* fonction qui va compter le nb de redirection */
/*************** marche dans cet etat **************/
void	redir_count_set(t_shell *shell, char **av)
{
	int		i;

	i = 0;
	shell->executor.nb_redir = 0;
	while (av[i])
	{
		if (is_redir(av[i]))
			shell->executor.nb_redir++;
		i++;
	}
	if (shell->executor.nb_redir > 0)
		set_redir_file(shell, av);
	else
	{
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
	}
}

void	set_redir_file(t_shell *shell, char **av)
{
	int i;
	int	j;

	i = ft_tablen(av) - 1;
	j = shell->executor.nb_redir;
	while (i > 0 && j > 0)
	{
		if (is_redir(av[i]) == TRUE)
			{
				j--;
				if (j == 0)
					break;
			}
		i--;
	}
	shell->executor.nb_redir--;
	if (shell->executor.redir_file != NULL)
		free(shell->executor.redir_file);
	if (av[i + 1])
		shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
	else
		shell->executor.redir_file = NULL;
	set_redir_type(shell, av[i]);
}

// char	**delet_redir(char **av)
// {
// 	char	**new_tab;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_tablen(av);
// 	new_tab = malloc(sizeof(char*) * len);
// 	if (!new_tab)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (av[i]) // pour tt copier sauf la var a suppr
// 	{
// 		if (is_redir(av[i]) == FALSE)
// 			new_tab[j++] = ft_strdup(av[i]);
// 		i++;
// 	}
// 	new_tab[j] = NULL;
// 	return (new_tab);
// }

char	**delete_redir(char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (!is_redir(av[i]))
		i++;
	new_tab = malloc(sizeof(char*) * (i + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (!is_redir(av[i]))
	{
		new_tab[i] = ft_strdup(av[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/* va mettre en place les infos a chaque fois qu on voit un > < >> */
/************* seems ok pas vraiment ok ******************/
// void	set_redir_file(t_shell *shell, char **av)
// {
// 	int i;
// 	int	j;

// 	i = ft_tablen(av) - 1;
// 	j = shell->executor.nb_redir;
// 	shell->executor.nb_redir_wip = shell->executor.nb_redir;
// 	while (i > 0 && j > 0)
// 	{
// 		if (is_redir(av[i]) == TRUE)
// 			{
// 				j--;
// 				if (j == 0)
// 					break;
// 			}
// 		i--;
// 	}
// 	shell->executor.nb_redir_wip--;
// 	if (shell->executor.redir_file != NULL)
// 		free(shell->executor.redir_file);
// 	if (av[i + 1])
// 		shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
// 	else
// 		shell->executor.redir_file = NULL;
// 	set_redir_type(shell, av[i]);
// 	shell->executor.redir_av = set_redir_av(shell->executor.av);
// }






































// char **delete_redir(char **av)
// {
// 	int count;
// 	int	i;
// 	int	j;

// 	count = 0;
// 	i = 0;
// 	while (av[i])
// 	{
// 		if (is_redir(av[i]))
// 			i += 2; // skip redir and filename
// 		else
// 		{
// 			count++;
// 			i++;
// 		}
// 	}

// 	char **new_tab = malloc(sizeof(char *) * (count + 1));
// 	if (!new_tab)
// 		return (NULL);

// 	i = 0;
// 	j = 0;
// 	while (av[i])
// 	{
// 		if (is_redir(av[i]))
// 			i += 2;
// 		else
// 			new_tab[j++] = ft_strdup(av[i++]);
// 	}
// 	new_tab[j] = NULL;
// 	return new_tab;
// }

// char	**delete_redir(char **av)
// {
// 	char	**new_tab;
// 	int		i;

// 	i = 0;
// 	while (!is_redir(av[i]))
// 		i++;
// 	new_tab = malloc(sizeof(char*) * (i + 1));
// 	if (!new_tab)
// 		return (NULL);
// 	i = 0;
// 	while (!is_redir(av[i]))
// 	{
// 		new_tab[i] = ft_strdup(av[i]);
// 		i++;
// 	}
// 	new_tab[i] = NULL;
// 	return (new_tab);
// }

// void create_redir_av(t_shell *shell)
// {
// 	printf("hello darkness my old friend\n");
// 	shell->executor.redir_av = shell->executor.av;

// 	if (shell->executor.nb_redir > 0)
// 	{
// 		shell->executor.redir_av = delete_redir(shell->executor.redir_av);
// 	}
// }


// cat < file.txt -> file.txt devient stdin
// echo hello > out.txt -> ecrit "hello" das out.txt (ecrase)
// echo again >> out.txt -> ajoute "again" a la fin de out.txt

