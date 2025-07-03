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

static void	create_fake_env(t_shell *shell);
static void	create_fake_exp(t_shell *shell);

void	cpy_envp(t_shell *shell, char **envp)
{
	if (!envp || *envp == NULL)
	{
		create_fake_env(shell);
		create_fake_exp(shell);
	}
	else
	{
		shell->cmd.envp_copy = init_envp_copy(shell, envp);
		shell->cmd.envp_exp = cpy_tab(shell, envp);
		bubble_tab(shell->cmd.envp_exp);
	}
}

static void	create_fake_env(t_shell *shell)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 4);
	if (!tmp)
		unfructuous_malloc(shell);
	tmp[0] = ft_strdup("?=0");
	tmp[1] = ft_strdup("PWD=/home/mlaffita/Documents/Minishell");
	tmp[2] = ft_strdup("SHLVL=2");
	tmp[3] = NULL;
	shell->cmd.envp_copy = tmp;
}

static void	create_fake_exp(t_shell *shell)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		unfructuous_malloc(shell);
	tmp[0] = ft_strdup("PWD=/home/mlaffita/Documents/Minishell");
	tmp[1] = ft_strdup("SHLVL=2");
	tmp[2] = NULL;
	shell->cmd.envp_exp = tmp;
}
