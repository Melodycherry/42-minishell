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

static char	*expand_var_segment(t_shell *shell, char *line, int *i, int *j);

char	*expand_all_vars_in_heredoc(t_shell *shell, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = expand_var_segment(shell, line, &i, &j);
		}
		else
			i++;
	}
	if (i > j)
		tmp = join_free(shell, tmp, &line[j], i - j);
	return (tmp);
}

static char	*expand_var_segment(t_shell *shell, char *line, int *i, int *j)
{
	char	*tmp;
	char	*rec_var;

	tmp = NULL;
	if (*i > *j)
		tmp = join_free(shell, tmp, &line[*j], *i - *j);
	(*i)++;
	*j = *i;
	while (line[*i] && (ft_isalnum(line[*i])
			|| line[*i] == '$' || line[*i] == '_'))
		(*i)++;
	if (*i > *j && var_exist(shell->cmd.envp_copy, &line[*j], *i - *j))
	{
		rec_var = recup_var(shell->cmd.envp_copy, &line[*j], *i - *j);
		tmp = join_free(shell, tmp, rec_var, ft_strlen(rec_var));
	}
	else
		tmp = join_free(shell, tmp, &line[*j], *i - *j);
	*j = *i;
	return (tmp);
}
