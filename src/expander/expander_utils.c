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

// Check si la variable existe dans l'export
// ***** seems GOOOOOOOOOD ******
t_bool	var_exist(char **envp, const char *var_env, int len)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i])) == 0
				&& (envp[i][len] == '='))
				return (TRUE);
		}
		else
			if (envp[i][len] == '\0')
				return (TRUE);
		i++;
	}
	return (FALSE);
}

// int	var_exist2(char **envp, const char *var_env, int len)
// {
// 	int		i;
// 	int		len_var;
// 	char	*equal_sign;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		equal_sign = ft_strchr(envp[i], '=');
// 		if (equal_sign)
// 		{
// 			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i])) == 0
// 				&& (envp[i][len] == '='))
// 				return (TRUE);
// 		}
// 		else
// 			if (envp[i][len] == '\0')
// 				return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }


// retourne la position dans le tableau env
// ********* a tester *********
int	pos_var_env(char **envp, char *var_env)
{
	int		i;
	int		len;
	char	*equal_sign;

	i = 0;
	len = ft_strlen(var_env);
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			if (ft_strncmp(envp[i], var_env, (int)(equal_sign - envp[i])) == 0
				&& (envp[i][len] == '='))
				return (i);
		}
		else
			if (envp[i][len] == '\0')
				return (i);
		i++;
	}
	return (i);
}

char	*join_free(char *s1, char *s2, int len_s2)
{
	size_t	len_s1;
	char	*str;

	if (s1)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	if (!s2)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(str, s1, len_s1 + 1);
		free(s1);
	}
	ft_strlcpy(str + len_s1, s2, len_s2 + 1);
	return (str);
}


//pour l instant sert a rien mais risque de servir
// **** a tester ****
t_bool	is_valid_var_name(t_token *token, t_shell *shell)
{
	int		i;
	char	*line;
	
	(void)shell;
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