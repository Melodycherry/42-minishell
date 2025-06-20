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

/**BUILTIN_UTILS**/
t_bool	is_builtin(char *cmd);

int		exec_builtin(t_shell *shell);

/**CD**/
int		builtin_cd(t_shell *shell, char **av);
void	execute_cd(t_shell *shell, char *path);
void	update_pwd(t_shell *shell, char *oldpwd);

/**ECHO**/
t_bool	is_flag_n(char *str);

int		builtin_echo(t_shell *shell, char **av);
int		print_flag_n(t_shell *shell, char **av, int *i);

/**ENV**/
void	print_tab(char **tab);
int		builtin_env(t_shell *shell, char **av);

/**EXIT**/
int		builtin_exit(t_shell *shell, char **av);

/**EXPORT**/
t_bool	checking_var(t_shell *shell, char *line);
t_bool	is_valid_name(char *line);

void	print_export(char **tab);
int		handle_export(t_shell *shell, char **av);
void	insert_env_export(t_shell *shell, char *value, char **old_tab, t_bool is_export);
void	put_in_env_export(t_shell *shell, char **old_tab, char *new_value, t_bool is_export);
	
/**PWD**/
int		builtin_pwd(t_shell *shell, char **av);

/**UNSET**/
int		builtin_unset(t_shell *shell, char **av);
void	remove_var(t_shell *shell, char **old_tab, char *name, t_bool is_export);

/*EXECUTOR*/
t_bool	is_absolative(char *str);

void	execution(t_shell *shell);

void	create_path(t_shell *shell, char **envp);
void	create_av(t_shell *shell, t_token *current);
void	exec_fork(t_shell *shell, char *pathname, char **av, char **envp);
void	exec_path(t_shell *shell, char *pathname, char **av, char **envp);
void 	exec_with_redir_check(t_shell *shell, char *pathname, char **av, char **envp);

/*PIPE*/

pid_t	fork_process_or_exit(void);

void	wait_for_all(void);
void	check_fd(int prev_fd);
void	exec_pipe(t_shell *shell);
void	init_pipe(t_shell *shell);
void	find_range(t_shell *shell);
void	create_redir_av(t_shell *shell);
void	create_pipe_or_exit(int *fd_pipe);
void	nb_pipe(t_shell *shell, t_token *token);
void	update_executor_state(t_shell *shell, char **pipe_av);
void	exec_pipe_child(t_shell *shell, int *fd_pipe, char **pipe_av, 
	int nb_pipe);

int		update_parent_fds(int *fd_pipe, int prev_fd, int nb_pipe);

/*REDIR*/

t_bool	is_redir(char *av);

void	handle_redir_in(char *file);
void	handle_redir_out(char *file);
void	handle_redir_append(char *file);
void	redir_handle(t_shell *shell);
void	set_redir_count(t_shell *shell, char **av);
void	set_redir_type(t_shell *shell, char *redir);
void	set_redir_file_type_av(t_shell *shell, char **av);
void	set_redir_file(t_shell *shell, char **av, int *i);

char	**set_redir_av(char **av);

//char	**extract_tab(char **av, int *i);
char	*strjoin_path(char *s1, char *s2);
char	*right_path(char **paths, char *cmd);
char	**split_args(t_shell *shell, char **av);

/*EXPANDER*/
t_bool	is_valid_var_name(t_token *token, t_shell *shell);
t_bool	var_exist(char **envp, const char *var_env, int i);

void	bubble_tab(char **tab);
void 	expansion(t_shell *shell);
void	delete_quotes_value(t_token *token);
void	cpy_envp(t_shell *shell, char **envp);
void	expand_var(t_shell *shell, t_token *token);
void	check_var_env(t_shell *shell, t_token *token);
void	set_env(char *value, int to_tab, t_shell *shell);
void	expand_single_quote(t_token *token, int *i, int *j);
void	expand_dollar(t_shell *shell, t_token *token, int *i, int *j);
void	expand_double_quote(t_shell *shell, t_token *token, int *i, int *j);

char	**cpy_tab(char **tab);
char	*join_free(char *s1, char *s2, int len_s2);
char	*recup_var(char **envp, char *var_env, int len);

int     ft_tablen(char **tab);
int		ft_strlen_plusplus(char *str);
int		pos_var_env(char **envp, char *var_env, int len);

/*LEXER*/
t_bool	ft_isquote(int c);
t_bool	is_next_quote(char quote, char *line, int i);

void	token_blank(t_shell *shell);
void	find_next_quote(char quote, char *line, int *i);

/*PARSER*/
t_bool	ft_isoperator(int c);
t_bool	is_token_error(t_token *token, t_shell *t_shell);

void	token_typedef(t_token *token);
void	token_operator(t_shell *shell);
void    insert_operator(t_shell *shell, int *i, int *j, t_token *current);
void    extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current);
void    extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current);

/*SIGNALS*/
void	setup_signals(void);
void	signal_handler(int sig);

/*UTILS*/

/**BYEBYE**/
t_token	*free_mid_list(t_token *current);

void    error_syntax_unset(char *line);
void    error_syntax_export(char *line);
void	free_token_list(t_shell *shell);
void	free_mid_tab(char **strs, int i);
void	free_tab(t_shell *shell, char **tab);

/**CHAIN**/
t_token	*create_token(int type, char *value, int n);

void	insert_base_list(t_tlist *tlist, t_token *token);
void	create_insert_token(t_shell *shell, int i, int j, t_token *current);
void	insert_mid_list(t_token *current, t_token *new_token, t_shell *shell);

/**INIT**/
void	init_all(t_shell *shell);
void	init_list(t_shell *shell);
void	init_executor(t_shell *shell);


// a placer
char    **malloc_tab(int tab_len);
void	fill_tab(char **new_tab, char**old_tab, int len);



//fonctions tests a supprimer apres
void	print_token(t_token *token, int (*f)(const char *, ...));
// void	print_token2(t_token *token, int (*f)(const char *, ...));
// void	print_token3(t_token *token, int (*f)(const char *, ...));
