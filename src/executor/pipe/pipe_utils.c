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

void find_range(t_shell *shell)
{
    int i;
    if (shell->executor.end < 0)
        i = 0;
    else
        i = shell->executor.end + 2; // +2 pour sauter le '|' (end+1 = '|', end+2 = début prochain)
    shell->executor.start = i;
    while (shell->executor.av[i] && ft_strcmp(shell->executor.av[i], "|") != 0)
        i++;
    shell->executor.end = i - 1;
}

// void	find_range(t_shell *shell) // version IJ 
// {
// 	int	i;

// 	i = shell->executor.end;
// 	if (i != 0 || shell->executor.start != 0)
// 		i++;
// 	shell->executor.start = i;
// 	while (shell->executor.av[i])
// 	{
// 		if (ft_strcmp(shell->executor.av[i], "|") == 0)
// 			break ;
// 		i++;
// 	}
// 	shell->executor.end = i - 1;
// }


char	**split_args(t_shell *shell, char **av) // copilot 
{
    char	**dest;
    int		i;
    int		start;
    int		end;

    find_range(shell); // met à jour start et end
    i = 0;
    start = shell->executor.start;
    end = shell->executor.end;
    if (end < start)
        return (NULL);
    dest = malloc(sizeof(char *) * (end - start + 2));
    if (!dest)
        return (NULL);
    while (start <= end && av[start])
        dest[i++] = ft_strdup(av[start++]);
    dest[i] = NULL;
    return (dest);
}
// char	**split_args(t_shell *shell, char **av) // version IJ
// {
//     char	**dest;
//     int		i;
//     int		start;
//     int		end;

//     // Sécurité : si end n'est pas initialisé, on le met à -1
//     if (shell->executor.end < 0)
//         shell->executor.end = -1;

//     find_range(shell);
//     i = 0;
//     start = shell->executor.start;
//     end = shell->executor.end;
//     if (end < start) // Rien à copier, retourne une commande vide
//         return (NULL);
//     dest = malloc(sizeof(char *) * (end - start + 2));
//     if (!dest)
//         return (NULL);
//     while (start <= end && av[start])
//     {
//         dest[i] = ft_strdup(av[start]);
//         i++;
//         start++;
//     }
//     dest[i] = NULL;
//     return (dest);
// }

void	nb_pipe(t_shell *shell, t_token *token)
{
	shell->executor.nb_pipe = 0;
	while (token->next)
	{
		if (token->type == T_PIPE)
			shell->executor.nb_pipe++;
		token = token->next;
	}
	printf("%d", shell->executor.nb_pipe);
}
int	has_pipe(t_shell *shell)
{
    int	i;

    if (!shell || !shell->executor.av)
        return (0);
    i = 0;
    while (shell->executor.av[i])
    {
        if (ft_strcmp(shell->executor.av[i], "|") == 0)
            return (1);
        i++;
    }
    return (0);
}