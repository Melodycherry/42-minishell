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

void    extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current)
{
    (*i) = (*i) + 2;
    create_insert_token(shell, *i, *j, current);
}

void    extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current)
{
    (*i)++;
    create_insert_token(shell, *i, *j, current);
}

void    insert_operator(t_shell *shell, int *i, int *j, t_token *current)
{
    char *value;

    value = current->value;
    (*j) = (*i);
    if (value[*i + 1] == '>' && value[*i] == '>')
        extract_dbl_token(shell, i, j, current);
    else if (value[*i + 1] == '<' && value[*i] == '<')
        extract_dbl_token(shell, i, j, current);
    else
        extract_sgl_token(shell, i, j, current);
}

void	last_token(t_shell	*shell, t_token *current)
{
	int i;
	int j;
	char *value;

	value = current->value;
	j = ft_strlen(value);
	
	i = j;
	while(!ft_isoperator(value[j]) && j > 0)
		j--;
	if (j < i)
	{
		create_insert_token(shell, i, (j + 1), current);
	}
	//free(current);
}

void    token_operator(t_shell *shell)
{
    int        i;
    int        j;
    char    *value;
    t_token *current;

    current = shell->tlist.head;
    while (current || current->next)
    {
        i = 0;
        value = current->value;
        while (value[i])
        {
            j = i;
            while(!ft_isquote(value[i]) && !ft_isoperator(value[i]) && value[i])
                i++;
            if (ft_isquote(value[i]))
                find_next_quote(value[i], value, &i);
            if (ft_isoperator(value[i]))
            {
                if (i > j)
                    create_insert_token(shell, i, j, current);
				insert_operator(shell, &i, &j, current);
            }
        }
		//last_token(shell, current);
        if (current->next) 
            current = current->next;
        else
		{
            break;
		}
    }
}
