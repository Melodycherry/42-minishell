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

void	delete_quotes_value(t_token *token)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (token->value[i])
	{
		j = i;
		while (token->value[i] && !ft_isquote(token->value[i]))
			i++;
		if (i > j)
			new_line = join_free(new_line, &token->value[j], (i - j));
		if (ft_isquote(token->value[i]) == TRUE)
		{
			j = i + 1;
			find_next_quote(token->value[i], token->value, &i);
			new_line = join_free(new_line, &token->value[j], (i - j - 1));
		}
		else
			return ;
	}
	free_ptr((void **)&token->value);
	token->value = new_line;
}

/** PDEMONT DIT C EST BON */
t_bool	is_quote_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
