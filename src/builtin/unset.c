/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

/** 
 * unset — unset values and attributes of variables and functions
 * Each variable or function specified by name shall be unset.
 * Unsetting a variable or function that was not previously set shall
	not be considered an error and does not cause the shell to abort.
 */
int	builtin_unset(t_shell *shell, char **av)
{
	int i;

	i = 1;
	if (av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return(2);
	}
	while ( av[i])
	{
		remove_var(shell, shell->cmd.envp_exp, av[i], TRUE);
		remove_var(shell, shell->cmd.envp_copy, av[i], FALSE);
		i++;
	}
	return (0);
}
// fonction pour supp la variable. Je vais refacto plus tard 
void	remove_var(t_shell *shell, char **old_tab, char *name, t_bool is_export)
{
	int len;
	int var_len;
	int i;
	int j;
	char **new_tab;

	len = ft_tablen(old_tab);
	var_len = ft_strlen(name);
	i = 0;
	j = 0;
	while (old_tab[i]) // on cherche si la variable est dans le tableau
	{
		if ((ft_strncmp(old_tab[i], name, var_len) == 0) && (old_tab[i][var_len] == '=' || old_tab[i][var_len] == '\0'))
			break;
		i++;
	}
	if(!old_tab[i]) // si on trouve pas on quitte
		return;
	new_tab = malloc(sizeof(char*) * len); // allocation du nouveau tableau. Len -1 + 1 pour '\0, donc juste len en fait 
	if (!new_tab)
		return;
	i = 0;
	j = 0;
	while (old_tab[i]) // pour tt copier sauf la var a suppr
	{
		if (!(ft_strncmp(old_tab[i], name, var_len) == 0 && (old_tab[i][var_len] == '=' || old_tab[i][var_len] == '\0')))
			new_tab[j++] = ft_strdup(old_tab[i]);
		i++;
	}
	new_tab[j] = NULL;
	if (is_export) // on remplace ancien tab par le nouveau 
	{
		free_tab(shell, shell->cmd.envp_exp);
		shell->cmd.envp_exp = new_tab;
	}
	else
	{
		free_tab(shell, shell->cmd.envp_copy);
		shell->cmd.envp_copy = new_tab;
	}
}
