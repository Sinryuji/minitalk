/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:50:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/06 20:03:06 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/libft/libft.h"
#include <unistd.h>

void	send_message_length(pid_t pid, unsigned int len)
{
	int	i;
	unsigned int	tmp;

	i = 0;
	tmp = len;
	while (i++ < 32)
	{
		len <<= 1;
		if (len >= tmp)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		tmp = len;
		usleep(100);
	}
}

void	send_message(pid_t pid, char *str)
{
	int	i;
	int	j;
	unsigned char	c;
	unsigned char	tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		c = (unsigned char)str[i];
		tmp = c;
		while (j++ < 8)
		{
			c <<= 1;
			if (c >= tmp)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			tmp = c;
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
		exit(1);
	pid = (pid_t)ft_atoi(argv[1]);
	send_message_length(pid, ft_strlen(argv[2]));
	usleep(100);
	send_message(pid, argv[2]);
	return (0);
}
