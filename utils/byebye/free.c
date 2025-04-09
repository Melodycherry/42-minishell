/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"

/***************************************************************************/
// C est les free du push swap pour les liste chainees
//a voir si on peut utiliser la base pour copier le double tableau de l envp
/***************************************************************************/

// void	ft_free(t_stack *stack)
// {
// 	t_node	*current;
// 	t_node	*next;

// 	if (!stack)
// 		return ;
// 	current = stack->head;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current);
// 		current = next;
// 	}
// }




/***************************************************************************/
// C est les free du so long
//a voir si on peut utiliser la base pour copier le double tableau de l envp
/***************************************************************************/

// char	**free_mid_tab(char **strs, int i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free (strs[i]);
// 	}
// 	free(strs);
// 	return (NULL);
// }

// char	**free_tab(t_mlx *mlx, char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (i < mlx->map.row)
// 	{
// 		free (tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (NULL);
// }