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

//fonction de test pour voir si la copie du tableau s est bien faite.
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_token(t_token *token, int (*f)(const char *, ...))
{
	int i;

	i = 0;
	if (!f)
		return ;
	while (token)
	{
		(*f)("token[%d] %s\n", i, token->value);
		//(*f)("token[%d] %d\n", i, token->type);
		(*f)("token[%d] %s\n", i, token->var_value);
		token = token->next;
		i++;
	}
}

// void	print_token2(t_token *token, int (*f)(const char *, ...))
// {
// 	int i;

// 	i = 0;
// 	if (!f)
// 		return ;
// 	while (token)
// 	{
// 		//(*f)("token[%d] %s\n", i, token->value);
// 		(*f)("token[%d] %d\n", i, token->type);
// 		token = token->next;
// 		i++;
// 	}
// }

// void	print_token3(t_token *token, int (*f)(const char *, ...))
// {
// 	int i;

// 	i = 0;
// 	if (!f)
// 		return ;
// 	while (token)
// 	{
// 		(*f)("token[%d] %s\n", i, token->var_value);
// 		//(*f)("token[%d] %s\n", i, token->type);
// 		token = token->next;
// 		i++;
// 	}
// }









/// DECHETS /// 




// //pour l instant sert a rien mais risque de servir
// // **** a tester ****
// t_bool is_valid_var_name(t_token *token, t_shell *shell)
// {
// 	int		i;
// 	char	*line;
	
// 	(void)shell;
// 	i = 0;
// 	line = token->value;
// 	while (line[i] && line[i] != '=')
// 	{
// 		if (line[0] == '_' || ft_isalpha(line[0]))
// 			i++;
// 		else 
// 			return (FALSE);
// 		if (line[i] == '_' || ft_isalnum(line[i]))
// 			i++;
// 	}
// 	return (TRUE);
// }



// tokensisation en fonction si on trouve des ' ' ou des "" et ''

// int	count_quotes(t_shell *shell, char quote, char c)
// {
// 	int		i;
// 	char	*line;
// 	int 	nb_quote;

// 	i = 0;
// 	nb_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == quote)
// 		{
// 			nb_quote++;
// 			i++;
// 			while (line[i] && line[i] != c)
// 				i++;
// 			if(line[i] == c)
// 				nb_quote++;
// 		}
// 		i++;
// 	}
// 	return (nb_quote);
// }

// int	count_single_quotes(t_shell *shell)
// {
// 	int		i;
// 	char	*line;
// 	int 	single_quote;

// 	i = 0;
// 	single_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			single_quote++;
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			if(line[i] == '\'')
// 				single_quote++;
// 		}
// 		i++;
// 	}
// 	printf("print single : %d\n", single_quote); // pour check le nbr
// 	return (single_quote);
// }
// int	count_double_quotes(t_shell *shell)
// {
// 	int		i;
// 	char	*line;
// 	int 	double_quote;

// 	i = 0;
// 	double_quote = 0;
// 	line = shell->cmd.line;
// 	while (line[i])
// 	{
// 		if (line[i] == '"')
// 		{
// 			double_quote++;
// 			i++;
// 			while (line[i] && line[i] != '"')
// 				i++;
// 			if(line[i] == '"')
// 				double_quote++;
// 		}
// 		i++;
// 	}
// 	printf("print double : %d\n", double_quote); // pour check le nbr
// 	return (double_quote);
// }

// int	check_quotes(t_shell *shell)
// {
//     // printf("print single : %d\n", count_quotes(shell, "")); // pour check le nbr
// 	if (count_quotes(shell, '\'') % 2 != 0)
// 		return (1);
// 	if (count_quotes(shell, '"') % 2 != 0)
// 		return (1);	
// 	return (0);
// }

// void	last_token(t_shell	*shell, t_token *current, int *j, int *i)
// {
// 	char *value;

// 	value = current->value;
// 	if (ft_isoperator(value[j - 1]))
// 	{
// 		return ;
// 	}
// 	i = j;
// 	while(!ft_isoperator(value[j]) && j > 0)
// 		j--;
// 	if (j < i)
// 	{
// 		create_insert_token(shell, i, (j + 1), current);
// 	}
// }

// char	*create_var(const char *name, const char *value)
// {
// 	int		len;
// 	char	*var;

// 	len = ft_strlen(name) + ft_strlen(value) + 2; // car '=' et '\0'
// 	var = malloc(len);
// 	if (!var)
// 		return (NULL);
// 	ft_strlcpy(var, name, len);
// 	ft_strlcat(var, "=", len);
// 	ft_strlcat(var, value, len);
// 	return(var);
// }







// fonction qui va verifier et enregistrer au besoin la line dans la var_value
// ********* en cours ne pas juger merci ********
// void	expand_var(t_shell *shell, t_token *token)
// {
// 	int		i;
// 	int		j;
// 	int		size_new_v;
// 	char	*value;
// 	char	*rec_var;

// 	value = token->value;
// 	i = 0;
// 	while (value[i])
// 	{
// 		j = i;
// 		while (value[i] && value[i] != '$' && value[i] != '"')
// 		{
// 			if (value[i] == '\'')
// 				find_next_quote('\'', value, &i);
// 			else
// 				i++;
// 		}
// 		if (value[i] == '$' || value[i] == '\0')
// 		{
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			if	(value[i] == '\0')
// 				return;
// 			i++;
// 			j = i;
// 			while (value[i] != '$' && value[i] && !ft_isquote(value[i])
// 				&& !ft_isspace(value[i])) 
// 				i++;
// 			if (var_exist(shell->cmd.envp_copy, &value[j], (i - j)) == TRUE)
// 			{
// 				rec_var = recup_var(shell->cmd.envp_copy, &value[j], (i - j));
// 				size_new_v = ft_strlen_plusplus(rec_var);
// 				token->var_value = join_free(token->var_value, rec_var, size_new_v);
// 			}
// 		}
// 		else if (value[i] == '"')
// 		{
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			i++;
// 			j = i;
// 			while (value[i] != '$' && value[i] && value[i] != '"') 
// 				i++;
// 			if (i > j)
// 				token->var_value = join_free(token->var_value, &value[j], (i - j));
// 			if(value[i] == '$')
// 			{
// 				if (var_exist(shell->cmd.envp_copy, &value[j], (i - j)) == TRUE)
// 				{
// 					rec_var = recup_var(shell->cmd.envp_copy, &value[j], (i - j));
// 					size_new_v = ft_strlen_plusplus(rec_var);
// 					token->var_value = join_free(token->var_value, rec_var, size_new_v);
// 				}
// 			}
// 		}
// 		printf("test : %s\n", token->var_value);
// 	}
// }



// void	delete_quotes_var_value(t_token *token)
// {
// 	int	i;
// 	int	j;
// 	char *new_line;

// 	i = 0;
// 	new_line = NULL;
// 	while (token->var_value[i])
// 	{
// 		j = i;
// 		while (token->var_value[i] && !ft_isquote(token->var_value[i]))
// 			i++;
// 		if	(token->value[i] == '\0')
// 			return;
// 		if (i > j)
// 			new_line = join_free(new_line, &token->value[j], (i - j));
// 		if (ft_isquote(token->var_value[i]) == TRUE)
// 		{
// 			j = i + 1;
// 			find_next_quote(token->var_value[i], token->var_value, &i);
// 			new_line = join_free(new_line, &token->var_value[j], (i - j - 1));
// 			i++;
// 		}
// 		else
// 			return ;
// 	}
// 	free(token->var_value);
// 	token->var_value = new_line;
// }