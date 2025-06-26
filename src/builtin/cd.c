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

/** 
 * cd — change the working directory
 * The cd utility shall change the working directory of the current
    shell execution environment (see Section 2.12, Shell Execution
    Environment) by executing the following steps in sequence.
 */
int	builtin_cd(t_shell *shell, char **av)
{
	char *path;
	char *home;
	
	if (av[1] && av[2])
	{
        ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
        return(1);
    }
	if (av[1] && av[1][0] == '-')
	{
		ft_putendl_fd("Invalid option", STDERR_FILENO);
		return(2);
	}
	if (!av[1]) // juste cd va dans HOME
	{
		home = recup_var(shell->cmd.envp_copy, "HOME", ft_strlen("HOME"));
		if (!home)
		{
            ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
            return(1);
        }
		path = home;
	}
	else	
		path = av[1];
	execute_cd(shell, path);
	return (0);
}

void	update_pwd(t_shell *shell, char *oldpwd)
{
	char *newpwd;
	char *oldpwd_str;
	char *newpwd_str;

	newpwd = getcwd(NULL, 0); // recup le current apres le chdir dans l'autre fonction 
	if (!newpwd)
		return;
	oldpwd_str = ft_strjoin("OLDPWD=", oldpwd); // pour creer le chemin avant
	if (!oldpwd)
		exit(EXIT_FAILURE); // gestion erreur !!!!!!!!!!
	newpwd_str = ft_strjoin("PWD=", newpwd); // et aussi le chemin apres ( donc actuel )
	if (!newpwd_str)
		exit(EXIT_FAILURE); // gestion erreur  !!!!!!!!!!
	if (oldpwd_str && newpwd_str)
	{
		set_env(oldpwd_str, TO_BOTH, shell); // modif l'env dans le shell 
		set_env(newpwd_str, TO_BOTH, shell);
    }
	free_ptr((void **)&oldpwd_str);
	free_ptr((void **)&newpwd_str);
	free_ptr((void **)&newpwd);
}

void	execute_cd(t_shell *shell, char *path)
{
	char *oldpwd;

	oldpwd = getcwd(NULL, 0); // save le current avant de changer 
	if (!oldpwd)
		return;
	if (chdir(path) == -1)
	{
		perror("cd");
		free_ptr((void **)&oldpwd);
		return;
	}
	update_pwd(shell, oldpwd); // si success on met a jour 
	free_ptr((void **)&oldpwd);
}
// check chdir ( change directory ) 
// int chdir(const char *path) -> retourne 0 si ok, -1 si erreur 
// check old_pwd ( a coder ) et aussi update the pwd

// on doit sauvegarder getcwd(NULL, 0) avant chdir
// appeler chdir(path)
// si marche appeler getcwd again, et modif les valeur de PWD et aussi OLDPWD dans l'env 

// on doit faire une fonction pour recup variable d'env ? get_env_value ? on les a deja ??? 
// !!! penser a free ! oldpwd et pwd 