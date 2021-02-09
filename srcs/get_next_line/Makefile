# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2020/12/23 22:01:36 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_MSG		= @echo "  \x1b[44m\x1b[38;2;16;19;33m\x1b[44m\x1b[01;37m        gnl \x1b[0m\x1b[34m\x1b[0m\x1b[0;90m $(1)\x1b[0m"

GNL_SRCS	= srcs/get_next_line.c \
			  srcs/get_next_line_utils.c
GNL_OBJS	= $(GNL_SRCS:.c=.o)

GNL_OUT		= "."
GNL_NAME	= libgnl.a

%.o : %.c
					@printf "  \x1b[44m\x1b[38;2;16;19;33m\x1b[44m\x1b[01;37m        gnl \x1b[0m\x1b[34m\x1b[0m\x1b[0;90m Compiling \x1b[0;34m$@...         \x1b[0m\r"
					@clang -Wall -Werror -Wextra -c $< -o $@ -O3 -march=skylake

$(GNL_NAME):	$(GNL_OBJS)
					@echo ""
					$(call GNL_MSG,"Linking objects into $(GNL_OUT)/$(GNL_NAME)")
					@ar -rcs $(GNL_OUT)/$(GNL_NAME) $(GNL_OBJS)
					$(call GNL_MSG,"Finished linking","\n")
					@echo ""

all:			$(GNL_NAME)

bonus:			$(GNL_NAME)

clean:
					@echo ""
					$(call GNL_MSG,"Deleting all objects...","\n")
					@rm -f $(GNL_OBJS)

fclean:			clean
					$(call GNL_MSG,"Deleting $(GNL_OUT)/$(GNL_NAME)...","\n")
					@rm -f $(GNL_OUT)/$(GNL_NAME)
					@echo ""

re:				fclean $(GNL_NAME)

.PHONY:			all bonus clean fclean re
