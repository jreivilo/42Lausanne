/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:23:30 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/14 17:23:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tty_attribute(int option)
{
	static int				i;
	static struct termios	old_termios;
	static struct termios	new_termios;

	if (!i++)
	{
		tcgetattr(0, &old_termios);
		new_termios = old_termios;
		new_termios.c_lflag &= ~ECHOCTL;
	}
	if (!option)
		tcsetattr(0, TCSANOW, &old_termios);
	else
		tcsetattr(0, TCSANOW, &new_termios);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
}

void	sigpassive(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		;
}

void	sigheredoc(int sig)
{
	if (sig == SIGQUIT)
		rl_redisplay();
}

void	set_signal(int option)
{
	struct sigaction	sa;

	if (!option)
	{
		sa.sa_handler = &sigpassive;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (option == 1)
	{
		sa.sa_handler = &sighandler;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = &sigheredoc;
		sa.sa_flags = SA_RESTART;
		signal(SIGINT, SIG_DFL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
