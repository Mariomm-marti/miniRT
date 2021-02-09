# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2021/02/09 20:21:22 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINIRT_MSG	= @echo "  \x1b[40m\x1b[38;2;16;19;33m\x1b[40m\x1b[01;37m     miniRT \x1b[0m\x1b[30m\x1b[0m\x1b[0;90m $(1)\x1b[0m"

MINIRT_SRCS	= srcs/error_handle.c \
			  srcs/main.c \
			  srcs/config/read_camera.c \
			  srcs/config/read_config.c \
			  srcs/config/read_cylinder.c \
			  srcs/config/read_light.c \
			  srcs/config/read_plane.c \
			  srcs/config/read_sphere.c \
			  srcs/config/read_square.c \
			  srcs/config/read_triangle.c \
			  srcs/config/read_values.c \
			  srcs/render/lookat.c \
			  srcs/render/render_cameras.c \
			  srcs/render/render_cylinders.c \
			  srcs/render/render_planes.c \
			  srcs/render/render_shadows.c \
			  srcs/render/render_spheres.c \
			  srcs/render/render_triangles.c
MINIRT_OBJS = $(MINIRT_SRCS:.c=.o)

MINIRT_OUT	= $(CURDIR)
MINIRT_NAME	= miniRT

MINIRT_LIBFT:= $(addprefix $(MINIRT_OUT),"/srcs/libft")
MINIRT_GNL	:= $(addprefix $(MINIRT_OUT),"/srcs/get_next_line")
SCREEN_WIDTH := $(shell osascript -e 'tell application "Finder" to get bounds of window of desktop' | grep -E "(\d{2,5})" -o | xargs | cut -d" " -f1)
SCREEN_HEIGHT := $(shell osascript -e 'tell application "Finder" to get bounds of window of desktop' | grep -E "(\d{2,5})" -o | xargs | cut -d" " -f2)

%.o : %.c
					@printf "  \x1b[40m\x1b[38;2;16;19;33m\x1b[40m\x1b[01;37m     miniRT \x1b[0m\x1b[30m\x1b[0m\x1b[0;90m Compiling \x1b[0;30m$@...                \x1b[0m\r"
					@clang -Wall -Werror -Wextra \
						-I$(MINIRT_LIBFT)/includes \
						-I$(MINIRT_GNL)/includes \
						-D SCREEN_WIDTH=$(SCREEN_WIDTH) -D SCREEN_HEIGHT=$(SCREEN_HEIGHT) \
						-c $< -o $@ -O3 -march=skylake

$(MINIRT_NAME):	depends $(MINIRT_OBJS)
					@echo ""
					@clang $(MINIRT_OBJS) -L$(MINIRT_OUT) \
						-lmlx -lft -lgnl -framework OpenGL -framework AppKit \
						-o $(MINIRT_OUT)/$(MINIRT_NAME) -O3 -march=skylake
					$(call MINIRT_MSG,"Finished compiling project!")

depends:
					$(call MINIRT_MSG,"Attempting to compile required dependencies...")
					@(test ! -f $(MINIRT_OUT)/libft.a && make -s -C $(MINIRT_LIBFT) math LIBFT_OUT=$(MINIRT_OUT)) || true
					@(test ! -f $(MINIRT_OUT)/libgnl.a && make -s -C $(MINIRT_GNL) GNL_OUT=$(MINIRT_OUT)) || true
					$(call MINIRT_MSG,"Finished compiling dependencies")
					$(call MINIRT_MSG,"Working on compiling miniRT...")
				

all:			$(MINIRT_NAME)

bonus:			$(MINIRT_NAME)

clean:
					$(call MINIRT_MSG,"Deleting dependencies")
					@rm -f $(MINIRT_OBJS)
					@rm -f $(MINIRT_OUT)/libft.a
					@rm -f $(MINIRT_OUT)/libgnl.a

fclean:			clean
					$(call MINIRT_MSG,"Cleaning dependencies objects...")
					@make -s -C $(MINIRT_LIBFT) fclean
					@make -s -C $(MINIRT_GNL) fclean
					$(call MINIRT_MSG,"Deleting $(MINIRT_OUT)/$(MINIRT_NAME)...")
					@rm -f $(MINIRT_OUT)/$(MINIRT_NAME)


re:				fclean $(MINIRT_NAME)


.PHONY:			depends all bonus clean fclean re 
