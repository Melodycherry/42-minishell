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

static int	skip_spaces(char *line, int i);
static int	handle_quote(char *line, int i);

void	token_blank(t_shell *shell)
{
	int		i;
	int		j;
	char	*line;
	t_token	*token;

	i = 0;
	line = shell->cmd.line;
	if (!line)
		return ;
	while (line[i])
	{
		i = skip_spaces(line, i);
		j = i;
		while (line[i] && !ft_isspace(line[i]))
			i = handle_quote(line, i);
		if (i > j)
		{
			token = create_token(shell, T_UNKNOWN, &line[j], (i - j));
			insert_base_list(&shell->tlist, token);
		}
	}
}

static int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

static int	handle_quote(char *line, int i)
{
	if (((line[i]) == '\'' || line[i] == '"')
		&& is_next_quote(line[i], line, i) == TRUE)
		find_next_quote(line[i], line, &i);
	else
		while (line[i] && !ft_isspace(line[i]) && !ft_isquote(line[i]))
			i++;
	return (i);
}
