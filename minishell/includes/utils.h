/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:23:59 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/14 17:23:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//SIGNAL
void	set_signal(int option);
void	tty_attribute(int option);
void	rl_replace_line(const char *text, int clear_undo);

//ENV
char	*get_env(char *name, char **env);

//PATH
char	*get_path_cmd(char *only_cmd, char **envp);

//ERROR
void	error_path(char *command);

#endif