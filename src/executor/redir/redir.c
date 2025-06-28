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

/* va verifier si presence de redir, les faire fonctionner et executer*/
/******** tout fonctionne pour un > ********/
void	redir_handle(t_shell *shell)
{
	t_token_type	type;

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