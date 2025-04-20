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

int		main(int ac, char **av, char **env);

/*BUILTIN*/

/*EXECUTOR*/

/*EXPANDER*/

/*LEXER*/
void	token_blank(t_shell *shell);
void	find_next_quote(char quote, char *line, int *i);
int		count_single_quotes(t_shell *shell);
int		count_double_quotes(t_shell *shell);

int		check_quotes(t_shell *shell);

t_bool	ft_isquote(int c);

/*PARSER*/

/*SIGNALS*/
void	setup_signals(void);
void	signal_handler(int sig);

/*UTILS*/
/*BYEBYE*/
int		check_error(t_shell *shell);
void	free_token_list(t_shell *shell);
void	free_mid_tab(char **strs, int i);
void	free_tab(t_shell *shell, char **tab);

/*CHAIN*/

/*INIT*/
void	bubble_tab(char **tab);
void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
void	cpy_envp(t_shell *shell, char **envp);
void	insert_base_list(t_tlist *tlist, t_token *token);

char	**cpy_tab(char **tab);

t_token	*create_token(int type, char *value, int n);





//fonctions tests a supprimer apres
void	print_tab(char **tab);
void	print_token(t_token *token, int (*f)(const char *, ...));
