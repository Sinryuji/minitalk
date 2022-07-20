/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:31:10 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/21 00:22:28 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_data	g_data;

static void	receive_connection_check(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_data.connection_flag == 0 && sig == SIGUSR1)
	{
		g_data.action.sa_sigaction = receive_message_length;
		sigaction(SIGUSR1, &g_data.action, NULL);
		sigaction(SIGUSR2, &g_data.action, NULL);
		g_data.connection_flag = 1;
		usleep(50);
		kill(info->si_pid, SIGUSR1);
	}
	else
	{
		usleep(50);
		kill(info->si_pid, SIGUSR2);
	}
}
#include <stdio.h>
static void	print_message(int *len, pid_t pid)
{
	g_data.msg[*len] = '\0';
	ft_printf("client[%d] : %s\n", pid, g_data.msg);
	*len = 0;
	g_data.len = 0;
	free(g_data.msg);
	g_data.msg = NULL;
	g_data.connection_flag = 0;
	g_data.action.sa_sigaction = receive_connection_check;
	sigaction(SIGUSR1, &g_data.action, NULL);
	sigaction(SIGUSR2, &g_data.action, NULL);
}

static void	receive_message(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	i = 0;
	static int	len = 0;

	(void)context;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	i++;
	if (i == 8)
	{
		g_data.msg[len] = c;
		c = 0;
		i = 0;
		len++;
	}
	if (g_data.len == len)
		print_message(&len, info->si_pid);
}

void	receive_message_length(int sig, siginfo_t *info, void *context)
{
	static int	i = 0;

	(void)info;
	(void)context;
	g_data.len <<= 1;
	if (sig == SIGUSR2)
		g_data.len |= 1;
	i++;
	if (i == 32)
	{
		i = 0;
		g_data.msg = ft_calloc((g_data.len + 1), sizeof(char));
		g_data.action.sa_sigaction = receive_message;
		sigaction(SIGUSR1, &g_data.action, NULL);
		sigaction(SIGUSR2, &g_data.action, NULL);
	}
}

int	main(void)
{
	ft_printf("Server PID : %d\n", getpid());
	g_data.action.sa_flags = SA_SIGINFO;
	g_data.action.sa_sigaction = receive_connection_check;
	sigemptyset(&g_data.action.sa_mask);
	sigaction(SIGUSR1, &g_data.action, NULL);
	sigaction(SIGUSR2, &g_data.action, NULL);
	while (1)
		pause();
	return (0);
}
