/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:44:44 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 20:44:46 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WO_RD 1
# define PI_PE 2
# define IN_RED 3
# define OUT_RED 4
# define HE_RDUC 5
# define AP_END 6

typedef struct s_env
{
	char			*var;
	char			*value;
	int				egnor;
	int				exit;
	struct s_env	*next;
	char			*pwd;
	char			**env;
}					t_env;

typedef struct t_file
{
	char			*name;
	int				infile;
	int				outfile;
	int				heredoc;
	int				apend;
	int				ambiguous;
	int				fd[2];
	int				expand;
	struct t_file	*next;
}					t_file;
typedef struct s_data
{
	char			**cmd;
	t_file			*file;
	struct s_data	*next;
}					t_data;

typedef struct s_us_var
{
	int				flag;
	// char *path ;
	char			**path_spt;
	char			*path_cmd;
	int				inpfd;
	int				outfd;
	int				fd;
	int				count_cmd;
	int				**pipe;
	int				*id;
	int				d;
	int				i;
	t_env			*envp;
	// char *str;
}					t_us_var;

typedef struct t_lexer
{
	char			*data;
	int				type;
	struct t_lexer	*next;
	struct t_lexer	*prev;
}					t_lexer;
typedef struct s_global
{
	int				exit_s;
	t_env			*env;
	t_data			*data;
	t_us_var		*var;
	int				flg;
}					t_global;

typedef struct t_var
{
	char			**cmd;
	t_file			*file;
	t_lexer			*new;
	int				sinqot;
	int				dobqot;
	int				i;
	int				j;
	char			*var;
	char			**newstr;
	int				n;
	char			*s;
	int				flg;
}					t_var;

void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *ptr, int c, size_t s);
int					ft_strlen(char *s);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strcmp(char *s1, char *s2);
int					ft_strchr(const char *s, int c);
char				*ft_strsrch(char *str, char c);
char				*ft_strncpy(char *dest, char *src, int size);
char				**ft_split(char *s, char c);
char				*join_wih_path(char *s1, char *s2);
char				*skip_char(char *s, char c);
int					ft_atoi(char *str);
char				*ft_itoa(int nb);

void				ft_putstr(char *str);
int					print_error1(char *s1, char *s2, char *s3);
int					print_error2(char *s1, char s2, char *s3);
int					check_rest(char *str, int i, int res, int sign);
int					check_long(int sign, long long res, char *str, int i);
int					ft_len(long nb);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				update_shell_level(t_env *envp);
void				add_default_path(t_env **envp);
void				initialize_environment(char **env, t_env **envp);
void				ft_add_node_to_env_list(t_env **env, t_env *new_node);
char				*ft_extract_variable_name(char *str);
int					update_existing_variable(char *var, char *value,
						t_env *envp);
void				ft_add_env_var(char *env_var, t_env **envp);
int					ft_access(t_us_var *var, t_data *data);
char				*get_path_cmd(t_us_var var, t_data *data);
char				*get_val(t_env *env, char *str);
int					count_heredoc(t_data *data);
void				read_from_heredoc(t_file *file, t_env *env);
int					wait_children(int pid, t_file *newfile);
int					heredoc(t_data *data, t_env *env);
void				close_herdoc(t_data *data);
int					ambiguous(t_file *file);
int					input_file(t_file *file, t_us_var *var);
int					output_file(t_file *file, t_us_var *var);
int					int_out_file(t_data *data, t_us_var *var);
int					count_listenv(t_env *env);
void				ft_print(t_env *s1);
void				sort_print(t_env *env);
int					pwd(t_data *data, t_env *env);
int					run_builtin_in_pipe(t_data *data, t_env **envp,
						t_us_var var);
int					other_builtin(t_data *data, t_env **envp);
int					run_builtin(t_data *data, t_env **envp);
void				run_first_cmd(t_data *data, t_us_var var, char **env,
						t_env **envp);
void				run_second_cmd(t_data *data, t_us_var var, char **env,
						t_env **envp);
void				run_last_cmd(t_data *data, t_us_var var, char **env,
						t_env **envp);
void				run_cmd_as_child(t_data *data, t_us_var var, char **env,
						t_env **envp);
void				init_pipe(t_us_var *var, t_data *data);
void				run_cmd_with_pipe(t_data **data, char **env, t_env **envp);
void				wait_for_children(t_us_var var, t_env *envp);
void				check_status(int status, t_env *envp);
void				free_node(t_data *tmp);
int					count_cmd(t_data *data);
void				run_cmd(t_data **data, char **env, t_env **envp);
void				dup_and_run(t_data *data, t_us_var var, t_env **envp,
						int flag);
int					is_builtin_command(char *cmd);
int					run_one_builtin(t_data *data, t_env **envp);
void				run_exuc(t_data *data, char **env, t_env *envp);
void				run_one_cmd(t_data *data, char **env, t_env **envp);
void				remove_env_var(t_env **envp, char *var_name);
int					unset(t_data *data, t_env **envp);
void				free_and_exit(t_data *data, t_us_var var, t_env *envp,
						int exit_s);

void				double_free(char **str);
void				free_file(t_file *file);
void				free_var(t_us_var *var);
void				free_exit(char *str, t_us_var var, int n, t_data *data);
int					ft_isalnumm(int c);
int					ft_check_str(char *str);
int					add__env_val(char *env, t_env **envp);
int					export(t_data *data, t_env **env);
void				ft_exit(t_data *data, t_env *envp);
int					count_env(t_env *env);
char				**get_envp(t_env *envp, char **env);
char				*ft_getenv(t_env *env, char *str);
void				print(t_env *envp);
int					env(t_data *data, t_env *evnp);
int					check_newline(t_data *data, int *i);
int					echo(t_data *data);
void				handle_no_argument(t_env *env, char *tmp);
void				change_and_free(char *oldpwd, char *newpwd, char *str,
						t_env *env);
int					handle_change_directory(t_data *data, t_env *env,
						char *tmp);
int					cd(t_data *data, t_env *env);
void				input_output_free(t_data *data, t_us_var *var);
void				handle_ctrl_c(int sig);
void				f(int sig);
void				free_data(t_data *data);
void				free_envp(t_env *envp);
void				child_handler(int signum);
void				child_handler1(int signum);
char				*add_tostr(char *str, t_var var, int *i);
void				other_conditio(t_var *var, char *str, t_env *envp);
int					ft_exit_statu(t_var *var, t_env *envp);
int					ft_exit_statu(t_var *var, t_env *envp);
char				*expending_herd(char *str, t_env *envp);
void				add_to_str(char *str, t_var *var);
void				expand_var(t_var *var, t_env *envp, int flag);
void				other_condition(t_var *var, char *str, t_env *envp,
						int flg);
int					ft_exit_status(t_var *var, t_env *envp);
char				**ft_expending_word(char *str, t_env *envp, int flg);
int					ft_outred(t_lexer **lexer, char *len);
int					ft_inreder(t_lexer **lexer, char *len);
int					ft_pipe(t_lexer **lexer, char *len);
int					ft_word(t_lexer **lexer, char *len);
void				ft_lexer(char *len, t_lexer **lexer);
void				apend_to_data(t_data **data, t_file **file, char ***cmd);
t_data				*ft_parsing(t_lexer *lexer, t_env *envp);
int					syntax_error1(t_lexer *lexer);
int					syntax_error(t_lexer **lexer);
void				ft_free1(char **str);
void				free_file(t_file *file);
void				free_envp(t_env *envp);
void				free_data(t_data *data);
void				free_var(t_us_var *var);
void				free_lexer(t_lexer *lexer);
int					count_str(char **str);
char				*apend_char_str(char *str, char c);
int					ft_copy(char **cmd, char **str);
int					count_list(t_data *data);
char				**ft_addstring(char **str, t_lexer *lexer, t_env *envp);
int					ft_printf(char *s1, char *s2, char *s3);
int					ft_printf1(char *s1, char s2, char *s3);
char				**ft_split_it(char *str);
char				**ft_catstr(char **str, char **str1);
char				*ft_strjoinn(char *s1, char *ss2);
void				check_word_expand(char *str, t_var *var);
int					is_whitespace(char c);
int					ft_token(char c, int *singl, int *doubl);
void				apend_in_struct(t_lexer **lexer, char *str, int type);
void				apend_to_file(t_lexer *lexer, int type, t_file **file,
						t_env *envp);
int					count_env(t_env *env);
void				free_herdoc(int exit_s, char *str);
char				*ft_getenv(t_env *env, char *str);
char				**get_envp(t_env *envp, char **env);
char				**ft_catstr(char **str, char **str1);
void				check_word_expand(char *str, t_var *var);
void				ft_execve(t_data *data, t_us_var var, t_env *envp,
						char **env);
#endif