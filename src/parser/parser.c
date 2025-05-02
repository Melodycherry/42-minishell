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

void    token_operator(t_shell *shell)
{
	int		i;
	int		j;
	int		check;
	char	*value;
	t_token	*current;

	check = 0;
	current = shell->tlist.head;
	while (current)
	{
		i = 0;
		value = current->value;
		j = i;
		while (value[i])
		{
			while(!ft_isquote(value[i]) && !ft_isoperator(value[i]) && value[i])
				i++;
			if (ft_isquote(value[i]))
				find_next_quote(value[i], value, &i);
			if (ft_isoperator(value[i]))
			{
				check++;
				if (i > j)
					create_insert_token(shell, i, j, current);
				insert_operator(shell, &i, &j, current);
				j = i;
			}
		}
		if (check > 0) 
		{
			if (i > j)
				create_insert_token(shell, i, j, current);
			current = free_mid_list(current);
			shell->tlist.token_cnt--;
			if (current != NULL)
				current = current->prev;
			check = 0;
		}
		if (current == NULL)
			break;
		if (current->next)
			current = current->next;
		else
			break;
	}
}

//mettre en place les type dans la chaine tlist
void token_typedef(t_token *token) //mettre la head de t list
{
	while(token) // ou while(token) a voir je sais jamais
	{
		if (token->value[0] == '|')
			token->type = T_PIPE;
		else if (token->value[0] == '>' && token->value[1] == '>')
			token->type = T_REDIR_APPEND;
		else if (token->value[0] == '<' && token->value[1] == '<')
			token->type = T_HEREDOC;
		else if (token->value[0] == '>')
			token->type = T_REDIR_OUT;
		else if (token->value[0] == '<')
			token->type = T_REDIR_IN;
		else
			token->type = T_WORD;
		token = token->next;
	}
	//handletoken error
	//definir les variable d expension  && EOF
	//apres mais dans une autre fonction : virer les "" dans les mots && EOF & autres
}
//gerer les cas d erreur a utiliser en parallele de typedef
t_bool	is_token_error(t_token *token, t_shell *shell)
{
	if (shell->tlist.token_cnt > 1)
	{	
		while (token) // 2 a 6 = operateur
		{
			if(token->next)
			{
				if (token->type == 3 && token->next->type == 4)
					token = token->next;
				else if ((token->type >= 2 && token->type <= 6) && (token->next->type >= 2 && token->next->type <= 6))
					return (TRUE);
			}
			token = token->next;
		}
	}
	return (FALSE);
}
