/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 17:30:29 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include "../../ft_printf/ft_printf.h"
# include "../../ft_printf/libft/libft.h"
# include <unistd.h>

typedef struct s_server_data
{
	struct sigaction	action;		
	int					len;
	char				*msg;
}	t_server_data;

/* server.c */
void	receive_message_length(int sig, siginfo_t *info, void *context);
void	receive_message(int sig, siginfo_t *info, void *context);

#endif
