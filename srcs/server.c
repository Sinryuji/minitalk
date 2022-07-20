/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:31:10 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 17:27:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "../ft_printf/ft_printf.h"

t_server_data	g_data;

void	receive_message(int sig)
{
	static char	c = 0;
	static int	i = 0;
	static int	len = 0;

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
	{
		g_data.msg[len] = '\0';
		ft_printf("%s", g_data.msg);
		len = 0;
		g_data.len = 0;
		free(g_data.msg);
		signal(SIGUSR1, receive_message_length);
		signal(SIGUSR2, receive_message_length);
	}
}

void	receive_message_length(int sig)
{
	static int	i = 0;

	g_data.len <<= 1;
	if (sig == SIGUSR2)
		g_data.len |= 1;
	i++;
	if (i == 32)
	{
		i = 0;
		g_data.msg = ft_calloc((g_data.len + 1), sizeof(char));
		signal(SIGUSR1, receive_message);
		signal(SIGUSR2, receive_message);
	}
}

int	main(void)
{
	ft_printf("Server PID : %d\n", getpid());
	signal(SIGUSR1, receive_message_length);
	signal(SIGUSR2, receive_message_length);
	while (1)
		pause();
	return (0);
}
