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
	printf("\n\n\n\n");
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
		token = token->next;
		i++;
	}
}








/// DECHETS /// 

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