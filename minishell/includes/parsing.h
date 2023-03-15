/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:34:15 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:40:46 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_brkt{
	int		i;
	int		j;
	int		cnt;
	int		quote;
	size_t	size_s;
}		t_brkt;

typedef struct s_swap{
	size_t	i;
	int		quote;
	char	*var;
	char	*tmp;
	char	*tmp_start;
}		t_swap;

typedef struct s_parsing_bracket
{
	int	i;
	int	j;
	int	cnt;
	int	quote;
}	t_parsing_bracket;

int		white_space(char c);

void	bracket_add(t_parsing_bracket *pb, char const *s);
void	bracket_tmp(t_parsing_bracket *pb, char const *s, char **tmp);

char	*ft_substr_minishell(char const *s, unsigned int start, size_t len);
void	categorizing(t_tree *tree, char **env);
void	classify(t_tree *tree, char **env);

char	**ft_split_parse(char const *s, char c);

char	*ft_substr_brkt(char const *s, int index);
void	ft_substr_brkt_init(t_brkt *data);
void	ft_substr_brkt_loop(char const **s, char **tmp, t_brkt *datas);
char	*ft_substr_brkt_2(char const *s, int index);

char	**parse_args(char	**args, char **env);
char	*parse_arg(char *arg, char **env);

char	*swap_var(char const *s, char **env);
char	*swap_var2(char const *s, char **env);
char	**ft_split_parse2(char const *s, char c);
void	ft_split_parse2a(int *word_count, char ***tmp, const char *s, char c);
int		ft_word_count_parse2(char const *s, char c);
size_t	define_size(char const *s, unsigned int index);

void	tokset(t_tree **tmp, char **word);
void	errset(t_tree **tmp, char **word);
void	pathset(t_tree **tmp, char **word);
void	buildset(t_tree **tmp, char **word);

void	var_swap_size2a(char const **s, char ***env, t_swap *data);
void	var_swap_size2b(char const **s, char ***env, t_swap *data);
int		not_alpha_num(char c);
size_t	var_length2(char const *s, char **env);

void	swap_var2a(char const **s, char ***env, t_swap *data);
void	swap_var2b(char const **s, char ***env, t_swap *data);
char	*var_in_env2(char const *s, char **env);

void	quote_dquote(char const *s, int *quote, char **tmp);
void	quote_dquote_count(char const *s, int *quote, int *i);

void	swap_var_dollar_quote(char const **s, char **env, char **tmp);
void	swap_var_dollar_no_quote(char const **s, char **env, char **tmp);
void	swap_var_quote_dquote(int *quote, char **tmp, char const **s);
void	var_swap_size_dollar_quote(size_t *i, char const **s, char **env);
void	var_swap_size_no_dollar_quote(size_t *i, char const **s, char **env);

void	init_pb(t_parsing_bracket *pb);
#endif