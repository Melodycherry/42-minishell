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

static void	filtr_out_var(char **old_tab, char **new_tab, char *name, int len);
static void	remove_var(t_shell *shell,
				char **old_tab, char *name, t_bool is_export);

int	builtin_unset(t_shell *shell, char **av)
{
	int	i;

	i = 1;
	if (av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return (2);
	}
	while (av[i])
	{
		remove_var(shell, shell->cmd.envp_exp, av[i], TRUE);
		remove_var(shell, shell->cmd.envp_copy, av[i], FALSE);
		i++;
	}
	return (0);
}

static void	remove_var(t_shell *shell,
				char **old_tab, char *name, t_bool is_export)
{
	int		i;
	int		var_len;
	char	**new_tab;
	//int		len;
	
	//len = ft_tablen(old_tab);
	var_len = ft_strlen(name);
	i = 0;
	while (old_tab[i])
	{
		if ((ft_strncmp(old_tab[i], name, var_len) == 0)
			&& (old_tab[i][var_len] == '=' || old_tab[i][var_len] == '\0'))
			break ;
		i++;
	}
	if (!old_tab[i])
		return ;
	new_tab = malloc_tab(shell, i - 1);
	filtr_out_var(old_tab, new_tab, name, var_len);
	replace_tab(shell, new_tab, is_export);
}

static void	filtr_out_var(char **old_tab, char **new_tab, char *name, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_tab[i])
	{
		if (!(ft_strncmp(old_tab[i], name, len) == 0
				&& (old_tab[i][len] == '=' || old_tab[i][len] == '\0')))
			new_tab[j++] = ft_strdup(old_tab[i]);
		i++;
	}
	new_tab[j] = NULL;
}

void	replace_tab(t_shell *shell, char **new_tab, t_bool is_export)
{
	if (is_export == TRUE)
	{
		free_tab(shell, &shell->cmd.envp_exp);
		shell->cmd.envp_exp = new_tab;
	}
	else
	{
		free_tab(shell, &shell->cmd.envp_copy);
		shell->cmd.envp_copy = new_tab;
	}
}
