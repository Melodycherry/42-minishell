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

int	handle_export(t_shell *shell, char **av)
{
	int len;
	int i;
	
	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return(2);
	}
	len = ft_tablen(av);
	i = 1;
	if (len == 1)
		print_export(shell->cmd.envp_exp);
	else
	{
		while (av[i])
		{
			checking_var(shell, av[i]);
			i++;
		}
	}
	return(0);
}


// checker si le nom de la variable est valide et fait la gestion des copies dans les tableaux
// ******* a tester ******
t_bool	checking_var(t_shell *shell, char *line)
{
	int		i;

	i = 0;
	if (is_valid_name(line) == FALSE)
		return (printf("C est pas valide var\n"), error_syntax_export(line), FALSE);
	
	while (line[i])
	{
		while (line[i] == '_' || ft_isalnum(line[i]))
			i++;
		if (line[i] == '=')
			return (set_env(line, TO_BOTH, shell), TRUE);
		else
			return (set_env(line, TO_EXPORT, shell), TRUE);
	}
	return (TRUE);
}

//mettre des information dans le envp_export et potientiellement dans le envp_copy
//********** a tester ********/
void	set_env(char *value, int to_tab, t_shell *shell)
{
	if (to_tab == TO_EXPORT)
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
	else if (to_tab == TO_BOTH)
	{
		insert_env_export(shell, value, shell->cmd.envp_exp, TRUE);
		insert_env_export(shell, value, shell->cmd.envp_copy, FALSE);
	}
}

//pour l instant sert a rien mais risque de servir
// **** a tester ****
t_bool is_valid_name(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '=')
	{
		if (line[0] == '_' || ft_isalpha(line[0]))
			i++;
		else 
			return (FALSE);
		if (line[i] == '_' || ft_isalnum(line[i]))
			i++;
	}
	return (TRUE);
}

char **malloc_tab(int tab_len)
{
	char **new_tab;

	new_tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!new_tab)
		return (NULL);
	return (new_tab);
}

void	fill_tab(char **new_tab, char**old_tab, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = ft_strdup(old_tab[i]);
		if (new_tab[i] == NULL)
			free_mid_tab(new_tab, i);
		i++;
	}
}

void	put_in_env_export(t_shell *shell, char **old_tab, char *new_value, t_bool is_export)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc_tab(ft_tablen(old_tab) + 1);
	while (i < ft_tablen(old_tab))
	{
		new_tab[i] = ft_strdup(old_tab[i]);
		if (new_tab[i] == NULL)
			free_mid_tab(new_tab, i);
		i++;
	}
	new_tab[i] = ft_strdup(new_value);
	i++;
	new_tab[i] = 0;
	if (is_export == TRUE)
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

// fonction de refactorisation qui va verifier l existance d une variable dans le env, recupere sa position
// la remplace si existante ou l ajoute sinon
// ****** a tester *********
void	insert_env_export(t_shell *shell, char *value, char **tab, t_bool is_export)
{
	int		index;
	int		var_len;
	char	*equal_sign;

	index = 0;
	equal_sign = ft_strchr(value, '=');
	if (equal_sign)
		var_len = (int)(equal_sign - value);
	else
		var_len = ft_strlen(value);
	if (var_exist(tab, value, var_len) == TRUE)
	{
		index = pos_var_env(tab, value, var_len);
		free_ptr((void **)&tab[index]);
		tab[index] = strndup(value, ft_strlen(value));
		return ;
	}
	if (var_exist(tab, value, var_len) == FALSE)
		put_in_env_export(shell, tab, value, is_export);
}

void	print_export(char **tab)
{
	int		i;
	char	*line;
	char	*equal_sign;

	i = 0;
	bubble_tab(tab);
	while (tab[i])
	{
		line = tab[i];
		equal_sign = ft_strchr(line, '=');
		if (equal_sign) // a check
			printf("declare -x %.*s=\"%s\"\n", (int)(equal_sign - line),
				line, equal_sign + 1);
		else
			printf("declare -x %s\n", line);
		i++;
	}
}