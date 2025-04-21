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

int	count_single_quotes(t_shell *shell)
{
	int		i;
	char	*line;
	int 	single_quote;

	i = 0;
	single_quote = 0;
	line = shell->cmd.line;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			single_quote++;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if(line[i] == '\'')
				single_quote++;
		}
		i++;
	}
	printf("print single : %d\n", single_quote); // pour check le nbr
	return (single_quote);
}
int	count_double_quotes(t_shell *shell)
{
	int		i;
	char	*line;
	int 	double_quote;

	i = 0;
	double_quote = 0;
	line = shell->cmd.line;
	while (line[i])
	{
		if (line[i] == '"')
		{
			double_quote++;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if(line[i] == '"')
				double_quote++;
		}
		i++;
	}
	printf("print double : %d\n", double_quote); // pour check le nbr
	return (double_quote);
}

int	check_quotes(t_shell *shell)
{
	if (count_single_quotes(shell) % 2 != 0)
		return (1);
	if (count_double_quotes(shell) % 2 != 0)
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
	(*i)++; // Si line[*i] atteint la fin de la chaîne (\0) sans trouver quote,
	// cela causera un accès mémoire invalide donc line[*i] 
	while (line[*i] && line[*i] != quote)
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
	if (!line)
    	return;
	while (line[i])
	{
		// skip space
		while( line[i] && ft_isspace(line[i]))
			i++;
		j = i;
		// on s'occupe des quote
		if((line[i]) == '\'' || line[i] == '"')
		{
			find_next_quote(line[i], line, &i);
			i++; // on doit aller apres la quote qui ferme !!
		}
		else
		{
			// avance jusqua un espace ou une quote 
			while(line[i] && !ft_isspace(line[i]) && !ft_isquote(line[i]))
				i++;
		}
		if (i > j)	// seulement si i plus grand que j comme ca token valide 
		{
			token = create_token(T_UNKNOWN, &line[j], (i - j));
			insert_base_list(&shell->tlist, token);
		}
	}
}

//          echo"salut"echo"salut" 
// echo "salut"

