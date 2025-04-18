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

// tokensisation en fonction si on trouve des ' ' ou des "" et ''

void	count_quotes(t_shell *shell)
{
	int		i;
	char	*line;

	i = 0;
	line = shell->cmd.line;
	while (line[i])
	{
		if (line[i] == 39)
		{
			shell->lexer.single_quote++;
			while (line[i] != 39 || line[i])
				i++;
			if(line[i] == 39)
				shell->lexer.single_quote++;
		}
		if (line[i] == 34)
		{
			shell->lexer.double_quote++;
			while (line[i] != 34 || line[i])
				i++;
			if(line[i] == 34)
				shell->lexer.double_quote++;
		}
		i++;
	}
}

int	check_quotes(t_shell *shell)
{
	if (shell->lexer.single_quote % 2 != 0)
		return (1);
	if (shell->lexer.double_quote % 2 != 0)
		return (1);	
	return (0);
}

t_bool	ft_isquote(int c)
{
	if ((c == '\'' || c == '"'))
		return (TRUE);
	return (FALSE);
}

void	find_next_quote(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] != quote)
		(*i)++;
}
void	token_blank(t_shell *shell)
{
	int		i;
	int		j;
	char	*line;
	t_token	*token;

	i = 0;
	j = 0;
	line = shell->cmd.line;
	while (line[i])
	{
		while(ft_isspace(line[i]))
		{
			i++;
			j = i;
		}
		if((line[i]) == '\'' || line[i] == '"')
			find_next_quote(line[i], line, &i);
		while(!ft_isspace(line[i]) && !ft_isquote(line[i]) && !line[i])
			i++;
		if (line[i] == '\0' || ft_isspace(line[i + 1]))	
		{
			token = create_token(T_UNKNOWN, &line[j], (i - j));
			insert_base_list(&shell->tlist, token);
		}
	}
}

//          echo"salut"echo"salut" 
// echo "salut"

