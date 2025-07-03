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

t_bool	is_next_quote(t_shell *shell, char quote, char *line, int i)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == '\0')
	{
		ft_putendl_fd("syntax error : quote expected. Minishell does not handle that", STDERR_FILENO);
		free_all(shell);
		exit(EXIT_FAILURE);
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
