# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2020/09/01 18:59:28 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINIRT_MSG	= @echo "\x1b[48;5;198m\x1b[38;5;15m\x1b[1m    miniRT\x1b[0m\x1b[0;90m $(1)\x1b[0m"

MINIRT_SRCS	= $(wildcard srcs/*.c)

MINIRT_OUT	= $(CURDIR)
MINIRT_NAME	= miniRT

MINIRT_LIBFT:= $(addprefix $(MINIRT_OUT),"/srcs/libft")
MINIRT_GNL	:= $(addprefix $(MINIRT_OUT),"/srcs/get_next_line")
MINIRT_FTPTF:= $(addprefix $(MINIRT_OUT),"/srcs/ft_printf")

$(MINIRT_NAME):
					$(call MINIRT_MSG,"Attempting to compile required dependencies...")
					@(test ! -f $(MINIRT_OUT)/libft.a && make -s -C $(MINIRT_LIBFT) LIBFT_OUT=$(MINIRT_OUT)) || true
					@(test ! -f $(MINIRT_OUT)/libgnl.a && make -s -C $(MINIRT_GNL) GNL_OUT=$(MINIRT_OUT)) || true
					@(test ! -f $(MINIRT_OUT)/libftprintf.a && make -s -C $(MINIRT_FTPTF) FTPTF_OUT=$(MINIRT_OUT) FTPTF_LIBFT=$(MINIRT_LIBFT)) || true
					$(call MINIRT_MSG,"Finished compiling dependencies")
					$(call MINIRT_MSG,"Working on compiling miniRT...")
					@clang -Wall -Werror -Wextra -L$(MINIRT_OUT) -lft -lgnl -lftprintf \
						-I$(MINIRT_LIBFT)/includes \
						-I$(MINIRT_GNL)/includes \
						-I$(MINIRT_FTPTF)/includes \
						$(MINIRT_SRCS) -o $(MINIRT_OUT)/$(MINIRT_NAME) -O3 -march=skylake
					$(call MINIRT_MSG,"Finished compiling project!")

all:			$(MINIRT_NAME)

bonus:			$(MINIRT_NAME)

clean:
					$(call MINIRT_MSG,"Deleting dependencies")
					@rm -f $(MINIRT_OUT)/libft.a
					@rm -f $(MINIRT_OUT)/libgnl.a
					@rm -f $(MINIRT_OUT)/libftprintf.a

fclean:			clean
					$(call MINIRT_MSG,"Deleting $(MINIRT_OUT)/$(MINIRT_NAME)...")
					@rm -f $(MINIRT_OUT)/$(MINIRT_NAME)

re:				fclean $(MINIRT_NAME)

.PHONY:			depends all bonus clean fclean re
