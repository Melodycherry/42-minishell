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
			if (!checking_var(token, shell))
				return(signal(SIGINT, signal_handler));
	else if (ft_strncmp(token->value, "export", ft_strlen(token->value)) == 0)
		print_export(shell->cmd.envp_copy);
	else
		return ;
}

void	print_export(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}
//pour l instant sert a rien mais risque de servir
// **** a tester ****
t_bool is_valid_var_name(t_token *token, t_shell *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = token->value;
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
// checker si le nom de la variable est valide et fait la gestion des copies dans les tableaux
// ******* a tester ******
t_bool checking_var(t_token *token, t_shell *shell)
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
			return (put_in_export(shell, shell->cmd.envp_exp, line), put_in_env(shell, shell->cmd.envp_copy, line), TRUE);
		else if (line[i] == ' ' && line[i] == '\0')
			return (put_in_export(shell, shell->cmd.envp_exp, line), TRUE);
		else 
			return (error_syntax_export(line), FALSE);		
	}
	return (TRUE);
}

//va ajouter en derniere ligne la new_value dans envp_exp et free l ancienne
// ******* a tester ******
void	put_in_export(t_shell *shell, char **old_export, char *new_value) //poutine export
{
	int		i;
	int		tab_len;
	char	**new_export;

	i = 0;
	new_export = malloc(sizeof(char *) * (ft_tablen(old_export) + 2));
	if (!new_export)
		return (NULL);
	while (i < ft_tablen(old_export))
	{
		new_export[i] = ft_strdup(old_export[i]);
		if (new_export[i] == NULL)
			free_mid_tab(cpy_tab, i);
		i++;
	}
	new_export[i] = ft_strdup(new_value[i]);
	i++;
	new_export[i] = 0;
	free_tab(shell, shell->cmd.envp_exp);
	shell->cmd.envp_exp = new_export;
}


//va ajouter en derniere ligne la new_value dans envp_copy et free l ancienne
// ******* a tester ******
void	put_in_env(t_shell *shell, char **old_env, char *new_value) //poutine env
{
	int		i;
	int		tab_len;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(old_env) + 2));
	if (!new_env)
		return (NULL);
	while (i < ft_tablen(old_env))
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (new_env[i] == NULL)
			free_mid_tab(cpy_tab, i);
		i++;
	}
	new_env[i] = ft_strdup(new_value[i]);
	i++;
	new_env[i] = 0;
	free_tab(shell, shell->cmd.envp_copy);
	shell->cmd.envp_copy = new_env;
}


// export + old ARG -> rien
// export + new ARG -> set dans env value="value_arg" /!\ de mettre des guillemets
// export + mot -> met le mot SANS GUILLEMET dans env

