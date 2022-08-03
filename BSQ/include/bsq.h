/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:03:37 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/03 12:07:21 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_info
{
	int		ligne;
	int		colonne;
	int		size_file;
	int		case_0;
	char	vide;
	char	obstacle;
	char	plein;
}	t_info;

typedef struct Square
{
	int		row;
	int		col;
	int		size;
}	t_square;

int			ft_atoi(char *str, int nbr);
int			ft_strlen(char *str);
int			cmp_c_charset(char c, char *charset);
int			nbr_strings(char *str, char *charset);
int			size_str(char *str, char *charset);
char		*cpy_str(char *str, char *charset);
char		**ft_split(char *str, char *charset);

int			ft_pre_instruction_std_entry(char ***tab2, t_info *info);
int			ft_pre_instruction(char ***tab2, char *argv, t_info *info);
int			ft_check_map(char *file, t_info *info);
int			ft_tot_length_file(char *file);
int			ft_check_info(t_info *info, char *tab);
char		*ft_file_to_buffer(char *file);
char		*ft_file_to_buffer_std_entry(void);
char		*ft_active_malloc(char *tab, char *buffer, int size);

t_square	solver(char **matrix, struct s_info info);
void		modify_square(char **matrix, struct Square sq);
void		replace(char **matrix, struct s_info info);
void		print_square(char **matrix, struct s_info info);
void		solve_and_print(char **matrix, struct s_info info);

#endif 
