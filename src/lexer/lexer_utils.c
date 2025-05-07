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

t_bool	ft_isquote(int c)
{
	if ((c == '\'' || c == '"'))
		return (TRUE);
	return (FALSE);
}
t_bool	is_next_quote(char quote, char *line, int i)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == '\0')
	{
		printf("On gere pas deso deso, faire la  gestion de sortie\n");
		exit(EXIT_FAILURE); //gerer partie free ou whatever
	}
	if (line [i] == quote)
		return (TRUE);
	return (FALSE);
}
void	find_next_quote(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	(*i)++;
}