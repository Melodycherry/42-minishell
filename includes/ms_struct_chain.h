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

#ifndef MS_STRUCT_CHAIN_H
# define MS_STRUCT_CHAIN_H

typedef struct s_list
{
	int		token_cnt; // peut etre util, a voir
	t_token	*head;

}	t_list; 

typedef struct s_token
{
	int		type;	 
	char	*value;
	t_token	*next;
	t_token	*prev;
}	t_token;

#endif