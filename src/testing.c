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

//fonction de test pour voir si la copie du tableau s est bien faite.
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n\n\n\n");
}

void	print_token(t_token *token, int (*f)(const char *, ...))
{
	int i;

	i = 0;
	if (!f)
		return ;
	while (token)
	{
		(*f)("token[%d]%s\n", i, token->value);
		token = token->next;
		i++;
	}
}
