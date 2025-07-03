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

int		main(int ac, char **av, char **env);

/*BUILTIN*/

t_bool	is_builtin(char *cmd);
t_bool	is_valid_name(char *line);

int		exec_builtin(t_shell *shell);
int		builtin_cd(t_shell *shell, char **av);
int		builtin_env(t_shell *shell, char **av);
int		builtin_pwd(t_shell *shell, char **av);
int		builtin_echo(t_shell *shell, char **av);
int		builtin_exit(t_shell *shell, char **av);
int		builtin_unset(t_shell *shell, char **av);
int		builtin_export(t_shell *shell, char **av);

char	**malloc_tab(t_shell *shell, int tab_len);

void	print_export(char **tab);
void	put_in_env_export(t_shell *shell, char **old_tab,
		char *new_value, t_bool is_export);
void	insert_env_export(t_shell *shell, char *value,
		char **tab, t_bool is_export);
void	replace_tab(t_shell *shell, char **new_tab, t_bool is_export);
		
t_bool	checking_var(t_shell *shell, char *line);

/*EXECUTOR*/

/**EXEC**/
t_bool	is_absolative(char *str);

void	execution(t_shell *shell);
void	handle_dup2(t_shell *shell, int fd, int std);
void	create_path(t_shell *shell, char **envp);
void	create_av(t_shell *shell, t_token *current);
void	exec_fork(t_shell *shell, char *pathname, char **av);
void	exec_path(t_shell *shell, char *pathname, char **av);
void	set_exit_status_env(t_shell *shell, int exit_status);
void	set_exit_status_env(t_shell *shell, int exit_status);

/**PIPE**/

pid_t	fork_process_or_exit(t_shell *shell);

void	wait_for_all(t_shell *shell, pid_t pid);
void	check_fd(t_shell *shell,int prev_fd);
void	exec_pipe(t_shell *shell);
void	init_pipe(t_shell *shell);
void	find_range(t_shell *shell);
void	update_parent_fds(int *prev_fd, int *fd_pipe, int nb_pipe);
void	create_pipe_or_exit(t_shell *shell, int *fd_pipe);
void	nb_pipe(t_shell *shell, t_token *token);
void	update_executor_state(t_shell *shell, char **pipe_av);
void	exec_pipe_child(t_shell *shell, int *fd_pipe, char **pipe_av,
			int nb_pipe);

char	*right_path(t_shell *shell, char **paths, char *cmd);
char	**split_args(t_shell *shell, char **av);

/**REDIR**/

t_bool	is_redir(char *av);

void	handle_redir_in(t_shell *shell, char *file);
void	handle_redir_out(t_shell *shell, char *file);
void	handle_redir_append(t_shell *shell, char *file);
void	redir_handle(t_shell *shell);
void	set_redir_count(t_shell *shell, char **av);
void	set_redir_type(t_shell *shell, char *redir);
void	set_redir_file_type_av(t_shell *shell, char **av);
void	set_redir_file(t_shell *shell, char **av, int *i);

char	**set_redir_av(t_shell *shell, char **av);

/*HEREDOC*/

void	check_error_fd(t_shell *shell, int fd);
void	unlink_file(t_shell *shell);
void	close_and_exit(t_shell *shell, int fd);
void	heredoc_exit_eof(t_shell *shell, int fd);
void	handle_heredoc(t_shell *shell);
void	nb_heredoc(t_shell *shell, t_token *token);
void	process_hd_file(t_shell *shell, char *file, char *eof, t_bool need_exp);

char	*create_name(t_shell *shell);
char	*expand_all_vars_in_heredoc(t_shell *shell, char *line);

/*EXPANDER*/

t_bool	is_quote_string(char *str);
t_bool	is_valid_var_name(t_token *token, t_shell *shell);
t_bool	var_exist(char **envp, const char *var_env, int i);

void	bubble_tab(char **tab);
void	expansion(t_shell *shell);
void	delete_quotes_value(t_shell *shell, t_token *token);
void	cpy_envp(t_shell *shell, char **envp);
void	expand_var(t_shell *shell, t_token *token);
void	check_var_env(t_shell *shell, t_token *token);
void	set_env(char *value, int to_tab, t_shell *shell);
void	expand_single_quote(t_shell *shell, t_token *token, int *i, int *j);
void	expand_dollar(t_shell *shell, t_token *token, int *i, int *j);
void	expand_double_quote(t_shell *shell, t_token *token, int *i, int *j);

char	**cpy_tab(t_shell *shell, char **tab);
char	**init_envp_copy(t_shell *shell, char **tab);
char	*join_free(t_shell *shell, char *s1, char *s2, int len_s2);
char	*recup_var(char **envp, char *var_env, int len);

int		ft_tablen(char **tab);
int		get_segment_len(char *str);
int		pos_var_env(char **envp, char *var_env, int len);

/*LEXER*/

t_bool	ft_isquote(int c);
t_bool	is_next_quote(t_shell *shell, char quote, char *line, int i);

void	token_blank(t_shell *shell);
void	find_next_quote(char quote, char *line, int *i);
void	insert_base_list(t_tlist *tlist, t_token *token);

/*PARSER*/

t_bool	ft_isoperator(int c);

t_token	*create_token(t_shell *shell, int type, char *value, int n);

char	*error_multiple_operator(t_token *token, t_shell *shell);

void	token_typedef(t_token *token);
t_bool	only_quote(t_token *token, char quote);
void	token_operator(t_shell *shell, t_token *current);
void	insert_operator(t_shell *shell, int *i, int *j, t_token *current);
void	extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current);
void	extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current);

/*SIGNALS*/
void	parent_signal(void);
void	child_signal(void);
void	heredoc_child_signal(void);
void	heredoc_parent_signal(void);
void	sigint_handler_child(int sig);
void	sig_core_dump_parent_signal(void);

/*UTILS*/

/**BYEBYE**/
t_token	*handle_free_mid_list(t_token *current);

void	close_fd(int *fd);
void	*free_ptr(void **ptr);
void	free_tab(char ***tab);
void	free_all(t_shell *shell);
void	free_all_minus_av(t_shell *shell);
void	free_and_reset(t_shell *shell);
void	error_syntax_unset(char *line);
// void	error_missing_delimiter(t_shell *shell);
// void	error_missing_delimiter(t_shell *shell);
void	error_syntax_export(char *line);
void	free_token_list(t_shell *shell);
// void	error_empty_token(t_shell *shell);
void	error_message(t_shell *shell, char *message);
// void	error_empty_token(t_shell *shell);
void	error_message(t_shell *shell, char *message);
void	error_syntax_token(t_shell *shell, char *value);
void	free_mid_tab(t_shell *shell, char ***strs, int i);
void	unfructuous_malloc(t_shell *shell);

/**CHAIN**/

void	create_insert_token(t_shell *shell, int i, int j, t_token *current);

/**INIT**/
void	init_all(t_shell *shell);

//fonctions tests a supprimer apres
void	print_token(t_token *token, int (*f)(const char *, ...));
void	print_tab(char **tab);