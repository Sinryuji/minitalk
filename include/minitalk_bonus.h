/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/21 20:22:55 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "../lib/ft_printf/lib/libft/include/libft.h"
# include "../lib/ft_printf/include/ft_printf.h"
# include <unistd.h>

typedef struct s_server_data
{
	struct sigaction	action;		
	int					len;
	char				*msg;
	int					connection_flag;
}	t_server_data;

/* server.c */
void	receive_message_length(int sig, siginfo_t *info, void *context);

/* client_handler_bonus.c */
void	receive_connection_reply(int sig);
void	receive_message_reply(int sig);

#endif
