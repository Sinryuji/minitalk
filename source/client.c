/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:50:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/21 20:23:22 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/colors.h"

static void	receive_connection_reply(int sig)
{
	if (sig == SIGUSR1)
		return ;
	if (sig == SIGUSR2)
		ft_puterr(RED "Connection to server failed, \
The server might be connecting with another client\n");
}

static void	send_connection_check(pid_t pid)
{
	int	cnt;
	int	sleep_time;

	cnt = 0;
	while (cnt < 10)
	{
		kill(pid, SIGUSR1);
		ft_printf("Connecting to server...\n");
		sleep_time = sleep(1);
		if (sleep_time != 0)
		{
			ft_printf(GREEN "Connection to server successful!\n");
			return ;
		}
		cnt++;
	}
	if (cnt == 10)
		ft_puterr(RED "Connection to server failed.\n");
}

static void	send_message_length(pid_t pid, int len)
{
	int	i;

	i = 32;
	while (i--)
	{
		if (len >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
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
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(50);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
		ft_puterr(RED "Invalid number of factors.\n" RESET \
GREEN "Usage: ./client [Server PID] [Message]\n" RESET);
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 101 || pid > 99998)
		ft_puterr(RED "Invalid PID\n" RESET);
	signal(SIGUSR1, receive_connection_reply);
	signal(SIGUSR2, receive_connection_reply);
	send_connection_check(pid);
	send_message_length(pid, ft_strlen(argv[2]));
	send_message(pid, argv[2]);
	ft_printf(GREEN "Message send complete!\n" RESET);
	return (0);
}
