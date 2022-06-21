# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 18:12:33 by hyeongki          #+#    #+#              #
#    Updated: 2022/06/21 18:32:27 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFALGS = -Wall -Wextra -Werror
SERVER_SRCS = server.c
CLIENT_SRCS = client.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
RM = rm -rf
AR = ar rcs
SERVER = server
CLIENT = client
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = libftprintf.a

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

all : $(SERVER) $(CLIENT)

$(SERVER) : $(SERVER_OBJS)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $^ $(FT_PRINTF_DIR)/$(FT_PRINTF) -o $@

$(CLIENT) : $(CLIENT_OBJS)
	make -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $^ $(FT_PRINTF_DIR)/$(FT_PRINTF) -o $@

clean : 
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C $(FT_PRINTF_DIR) clean

fclean : clean
	$(RM) $(SERVER) $(CLIENT)
	make -C $(FT_PRINTF_DIR) fclean

re : fclean all

.PHONY :
	all clean fclean re
