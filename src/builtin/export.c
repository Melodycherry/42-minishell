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

// fonction principale pour l'export 
// ******* a tester ******
void	handle_export(t_shell *shell, t_token *token)
{
	if (ft_strncmp(token->value, "export", ft_strlen(token->value)) == 0
		&& token->next->type == T_WORD)
	{
		if (checking_var(token, shell) == FALSE)
			return ;//pas juste, doit retourner qqc mais on c est pour futur noud
	}
	else if (ft_strncmp(token->value, "export", ft_strlen(token->value)) == 0)
		print_export(shell->cmd.envp_copy);
	else
		return ;
}

void	print_export(char **tab)
{
	int		i;
	char	*line;
	char	*equal_sign;

	i = 0;
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

// checker si le nom de la variable est valide et fait la gestion des copies dans les tableaux
// ******* a tester ******
t_bool	checking_var(t_token *token, t_shell *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = token->value;
	while (line)
	{
		if (line[0] == '_' || ft_isalpha(line[0]))
			i++;
		else
			return (error_syntax_export(line), FALSE);
		if (line[i] == '_' || ft_isalnum(line[i]))
			i++;
		else if (line[i] == '=')
			return (set_env(line, TO_BOTH, shell), TRUE);
		else if (line[i] == ' ' && line[i] == '\0')
			return (set_env(line, TO_EXPORT, shell), TRUE);
		else
			return (error_syntax_export(line), FALSE);		
	}
	return (TRUE);
}

//va ajouter en derniere ligne la new_value dans envp_exp et free l ancienne
// ******* a tester ******
void	put_in_env_export(t_shell *shell, char **old_tab,
			char *new_value, t_bool is_export)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc(sizeof(char *) * (ft_tablen(old_tab) + 2));
	if (!new_tab)
		return ;
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
	free_tab(shell, shell->cmd.envp_exp);
	if (is_export)
		shell->cmd.envp_exp = new_tab;
	else
		shell->cmd.envp_copy = new_tab;
}

// fonction de refactorisation qui va verifier l existance d une variable dans le env, recupere sa position
// la remplace si existante ou l ajoute sinon
// ****** a tester *********
void	insert_env_export(t_shell *shell, char *value, char **tab, t_bool is_export)
{
	int	index;

	index = 0;
	if (var_exist(tab, value, ft_strlen(value)))
	{
		index = pos_var_env(tab, value);	
		free(tab[index]);
		tab[index] = strndup(value, ft_strlen(value));
	}
	else
		put_in_env_export(shell, tab, value, is_export);
}
