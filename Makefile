# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 18:12:33 by hyeongki          #+#    #+#              #
#    Updated: 2022/07/21 18:16:54 by hyeongki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFALGS = -Wall -Wextra -Werror
SRCS_PATH = ./srcs/
SERVER_SRCS_NAME = server.c
CLIENT_SRCS_NAME = client.c
SERVER_SRCS = $(addprefix $(SRCS_PATH), $(SERVER_SRCS_NAME))
CLIENT_SRCS = $(addprefix $(SRCS_PATH), $(CLIENT_SRCS_NAME))
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
BONUS_PATH = $(SRCS_PATH)bonus/
SERVER_BONUS_SRCS_NAME = server_bonus.c
CLIENT_BONUS_SRCS_NAME = client_bonus.c client_handler_bonus.c
SERVER_BONUS_SRCS = $(addprefix $(BONUS_PATH), $(SERVER_BONUS_SRCS_NAME))
CLIENT_BONUS_SRCS = $(addprefix $(BONUS_PATH), $(CLIENT_BONUS_SRCS_NAME))
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)
RM = rm -rf
AR = ar rcs
NAME = minitalk
SERVER = server
CLIENT = client
FT_PRINTF_PATH = ./ft_printf
FT_PRINTF = libftprintf.a

ifdef BONUS_FLAG
	SERVER_OBJECTS = $(SERVER_BONUS_OBJS)
	CLIENT_OBJECTS = $(CLIENT_BONUS_OBJS)
else
	SERVER_OBJECTS = $(SERVER_OBJS)
	CLIENT_OBJECTS = $(CLIENT_OBJS)
endif

%.o : %.c
	$(CC) $(CFALGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(SERVER) $(CLIENT)

$(SERVER) : $(SERVER_OBJECTS)
	make -C $(FT_PRINTF_PATH)
	$(CC) $(CFLAGS) $^ $(FT_PRINTF_PATH)/$(FT_PRINTF) -o $@

$(CLIENT) : $(CLIENT_OBJECTS)
	make -C $(FT_PRINTF_PATH)
	$(CC) $(CFLAGS) $^ $(FT_PRINTF_PATH)/$(FT_PRINTF) -o $@

bonus :
	$(MAKE) BONUS_FLAG=1 all

clean : 
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS)
	make -C $(FT_PRINTF_PATH) clean

fclean : clean
	$(RM) $(SERVER) $(CLIENT)
	make -C $(FT_PRINTF_PATH) fclean

re : fclean all

.PHONY :
	all clean fclean re
