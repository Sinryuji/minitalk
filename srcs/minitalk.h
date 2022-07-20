/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:51:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 17:27:46 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include "../ft_printf/libft/libft.h"

typedef struct s_server_data
{
	int					len;
	char				*msg;
}	t_server_data;

/* server.c */
void	receive_message_length(int sig);
void	receive_message(int sig);

#endif
