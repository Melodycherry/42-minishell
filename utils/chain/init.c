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

// void	init_list(t_stack *stack)
// {
// 	stack->head = NULL;
// 	stack->cnt_node = 0;
// 	stack->idx_max = 0;
// 	stack->idx_min = 0;
// }

// t_node	*create_node(int value)
// {
// 	t_node	*new_node;

// 	new_node = malloc(sizeof(t_node));
// 	if (!new_node)
// 		return (NULL);
// 	ft_memset(new_node, 0, sizeof(t_node));
// 	new_node->value = value;
// 	return (new_node);
// }

// void	insert_node_back(t_stack *stack, t_node *new_node)
// {
// 	t_node	*current;

// 	if (!new_node || !stack)
// 		return ;
// 	if (!stack->head)
// 	{
// 		stack->head = new_node;
// 		stack->cnt_node = 1;
// 	}
// 	else
// 	{
// 		current = stack->head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_node;
// 		new_node->prev = current;
// 		stack->cnt_node++;
// 	}
// }