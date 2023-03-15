/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:20:52 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/14 09:20:52 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

typedef struct s_export{
	int		i;
	int		j;
	int		k;
	char	**env_cpy;
	char	*tmp;
	char	**tmp1;
	char	**tmp2;
	char	*tmp_arg;
	char	*new_arg;
	char	*tmp_new_arg;
}	t_export;

int		ft_cd(char **path, char **env);
int		ft_echo(char **args, char **env);
int		ft_env(char **env);
int		ft_exit(char **args);
int		ft_export(char	***env, char **args);
int		ft_pwd(void);
int		ft_unset(char **args, char ***env);
int		ft_cd_error1(char **argv);
int		ft_cd_error2(char **argv);
int		ft_echo_error(char **args);
int		ft_exit_error(char **args);
char	**ft_add_env1(t_export *data, char **args, char ***envs);
char	**ft_add_env2(t_export *data, char **arg, char ***env);
void	ft_print_tab_unique1(t_export *data, char ***tabs, char ***tabs2);
void	ft_export1(t_export *data, char ***arg, \
	char ****envs, char ***env_cpy2);
void	ft_export2(t_export *data, char ***env_cpy2);
void	ft_export3(char ***env_cpy2, char ****envs);
void	ft_export4(t_export *data, char ***arg, \
		char ****envs, char ***env_cpy2);
void	ft_print_tab(char **tab);
char	*return_arg(char *arg);
int		len_until_equal(char *arg);
void	ft_print_tab_unique(char **tab, char **tab2);
void	ft_print_tab_unique1(t_export *data, char ***tabs, char ***tabs2);
char	*add_double_quotes(char *arg);
char	*ft_strndup(char *str, int n);
void	remove_quotes(char **args);
int		ft_strcpy(char *dest, char *src);
char	**sort_tab(char **tab);
char	**ft_add_env(char **env, char *arg);

#endif