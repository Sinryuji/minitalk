/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 19:33:03 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include "../ft_printf/libft/libft.h"
# include "../ft_printf/ft_printf.h"

typedef struct s_server_data
{
	struct sigaction	action;
	int					len;
	char				*msg;
	int					connection_flag;
}	t_server_data;

/* server.c */
void	receive_message_length(int sig, siginfo_t *info, void *context);

#endif
