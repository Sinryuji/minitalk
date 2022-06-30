/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:30 by hyeongki          #+#    #+#             */
/*   Updated: 2022/06/30 19:47:59 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_data;

void	action(int sig)
{
	if (g_data.cnt++ < 8)
	{
		g_data.c <<= 1;
		if (sig == SIGUSR2)
			g_data.c |= 1;
	}
	else
	{
		write(1, &g_data.c, 1);
		g_data.c = 0;
		g_data.cnt = 0;
	}
}

int	catch_signal(int sig, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return (sigaction(sig, &action, NULL));
}

int	main()
{
	ft_printf("Server PID : %d\n", getpid());
	catch_signal(SIGUSR1, action);
	catch_signal(SIGUSR2, action);
	while (1)
		pause();
	return (0);
}
