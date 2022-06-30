/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:50:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/06/30 19:23:12 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	parse_signal(pid_t pid, char *str)
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
		kill(pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
		exit(1);
	pid = (pid_t)ft_atoi(argv[1]);
	parse_signal(pid, argv[2]);
	return (0);
}
