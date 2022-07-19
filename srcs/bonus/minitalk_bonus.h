/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/19 19:56:20 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>

# define TRUE 1
# define FALSE 0

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
