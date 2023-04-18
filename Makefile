# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 17:30:23 by marvin            #+#    #+#              #
#    Updated: 2023/04/18 17:37:32 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft/
LIBFT = libft.a

NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

SRCS_SERVER = server.c utils.c
SRCS_CLIENT = client.c utils.c
SRCS_SERVER_BONUS = server_bonus.c utils.c
SRCS_CLIENT_BONUS = client_bonus.c utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

DEPS_SERVER = $(SRCS_SERVER:.c=.d)
DEPS_CLIENT = $(SRCS_CLIENT:.c=.d)
DEPS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.d)
DEPS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.d)

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@make -C $(LIBFT_DIR) bonus
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME_SERVER) $(NAME_CLIENT)
	@make -C $(LIBFT_DIR) bonus

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT_DIR)$(LIBFT) -o $@
-include $(DEPS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT_DIR)$(LIBFT) -o $@
-include $(DEPS_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	@make -C $(LIBFT_DIR) bonus

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT_DIR)$(LIBFT) -o $@
-include $(DEPS_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT_DIR)$(LIBFT) -o $@
-include $(DEPS_CLIENT_BONUS)
	
clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(DEPS_SERVER) $(DEPS_CLIENT)
	$(RM) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS) $(DEPS_SERVER_BONUS) $(DEPS_CLIENT_BONUS)
	
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)	$(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS) 

re: fclean all

.PHONY: all clean fclean re bonus
