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

static char	*strjoin_path(t_shell *shell, char *s1, char *s2);

void	create_av(t_shell *shell, t_token *current)
{
	int		i;
	char	**av;

	i = 0;
	av = malloc(sizeof(char *) * (shell->tlist.token_cnt + 1));
	if (!av)
		return (perror("malloc\n"));
	while (i < shell->tlist.token_cnt)
	{
		if (current->type == T_ARG)
			av[i] = ft_strdup(current->var_value);
		else
			av[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	av[i] = NULL;
	free_tab(&shell->executor.av);
	shell->executor.av = av;
}

void	create_path(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i])
		shell->executor.paths = ft_split(envp[i] + 5, ':');
	else
		shell->executor.paths = NULL;
}

char	*right_path(t_shell *shell, char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = strjoin_path(shell, paths[i], cmd);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			//else
			// 	gestion d erreur //TODO: 
		}
		free_ptr((void **)&path);
		i++;
	}
	return (NULL);
}

t_bool	is_absolative(char *str)
{
	if (ft_strchr(str, '/'))
		return (TRUE);
	return (FALSE);
}

static char	*strjoin_path(t_shell *shell, char *s1, char *s2)
{
	char	*dest;
	char	*tmp;

	(void)shell;
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		unfructuous_malloc(shell);
	dest = ft_strjoin(tmp, s2);
	free_ptr((void **)&tmp);
	return (dest);
}
