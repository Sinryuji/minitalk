/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:50:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 17:29:52 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "colors_bonus.h"

int	g_signal;

static void	receive_reply(int sig)
{
	if (sig != g_signal)
		ft_puterr(RED "Received wrong reply\n");
	g_signal = 0;
}

static void	send_message_length(pid_t pid, unsigned int len)
{
	int				i;

	i = 32;
	while (i--)
	{
		if (len >> i & 1)
		{
			kill(pid, SIGUSR2);
			g_signal = SIGUSR2;
		}
		else
		{
			kill(pid, SIGUSR1);
			g_signal = SIGUSR1;
		}
		pause();
		usleep(50);
	}
}

static void	send_message(pid_t pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 8;
		c = (unsigned char)*str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				kill(pid, SIGUSR2);
				g_signal = SIGUSR2;
			}
			else
			{
				kill(pid, SIGUSR1);
				g_signal = SIGUSR1;
			}
			pause();
			usleep(50);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
		ft_puterr(RED "Invalid number of factors.\n" RESET \
GREEN "Usage: ./client [Server PID] [Message]\n" RESET);
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 101 || pid > 99998)
		ft_puterr(RED "Invalid PID\n" RESET);
	signal(SIGUSR1, receive_reply);
	signal(SIGUSR2, receive_reply);
	send_message_length(pid, ft_strlen(argv[2]));
	send_message(pid, argv[2]);
	ft_printf(GREEN "Message send complete!\n" RESET);
	return (0);
}
