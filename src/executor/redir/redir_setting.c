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

/* fonction qui va faire la gestion des settings */
/*************** marche dans cet etat **************/
void set_redir_file_type_av(t_shell *shell, char **av)
{
	int i;
	
	i = 0;
	set_redir_file(shell, av, &i);
	if (av[i + 1] == NULL)
	{
		fprintf(stderr, "Syntax error: expected file after redirection\n"); //gestion d erreur a refaire
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
		return;
	}
	if (shell->executor.redir_file != NULL)
		free(shell->executor.redir_file);
	shell->executor.redir_file = ft_strndup(av[i + 1], ft_strlen(av[i + 1]));
	set_redir_type(shell, av[i]);
	shell->executor.redir_av = set_redir_av(av);
}

/* fonction qui va set le type de redirection. elle etait dure celle la */
/*************** marche dans cet etat **************/
void set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0 )
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, ">>") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
}

/* fonction qui va compter le nb de redirection */
/*************** marche dans cet etat **************/
void	set_redir_count(t_shell *shell, char **av)
{
	int		i;

	i = 0;
	shell->executor.nb_redir = 0;
	while (av[i])
	{
		if (is_redir(av[i]))
			shell->executor.nb_redir++;
		i++;
	}
	if (shell->executor.nb_redir > 0)
		set_redir_file_type_av(shell, av);
	else
	{
		shell->executor.redir_file = NULL;
		shell->executor.redir_type = 0;
	}
}

/* fonction qui va set le fichier juste apres la redir */
/*************** marche dans cet etat **************/
void	set_redir_file(t_shell *shell, char **av, int *i)
{
	int redir_count;

	redir_count = 0;
	while (av[*i])
	{
		if (is_redir(av[*i]) == TRUE)
			redir_count++;
		(*i)++;
	}
	shell->executor.nb_redir = redir_count;
	shell->executor.nb_redir_wip = redir_count;
	*i = ft_tablen(av) - 1;
	while (*i > 0)
	{
		if (is_redir(av[*i]) == TRUE)
			break;
		(*i)--;
	}

}

/* fonction qui va supprimer ce qu il y a apres l redir */
/**** tres surement fausse, si je dis pas de betise, il faut juste enlever ""> + file"*/
/*************** faux mais marche dans cet etat **************/

char	**set_redir_av(char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (!is_redir(av[i]))
		i++;
	new_tab = malloc(sizeof(char*) * (i + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (!is_redir(av[i]))
	{
		new_tab[i] = ft_strdup(av[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

