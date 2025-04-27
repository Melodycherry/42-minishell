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
		return ;
	while (line[i])
	{
		// skip space
		while (line[i] && ft_isspace(line[i]))
			i++;
		j = i;
		while (line[i] && !ft_isspace(line[i]))
		{
			// on s'occupe des quote
			if (((line[i]) == '\'' || line[i] == '"')
				&& is_next_quote(line[i], line, i) == TRUE)
				find_next_quote(line[i], line, &i);
			else
			{
				// avance jusqua un espace ou une quote 
				while (line[i] && !ft_isspace(line[i]) && !ft_isquote(line[i]))
					i++;
			}
		}
		if (i > j) // seulement si i plus grand que j comme ca token valide 
		{
			token = create_token(T_UNKNOWN, &line[j], (i - j));
			insert_base_list(&shell->tlist, token);
		}
	}
}
