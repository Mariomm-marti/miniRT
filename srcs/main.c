/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:18:44 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/04 20:02:52 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/config.h"
#include <stdio.h> //
#include <libft.h>
#include <mlx.h>

static int	handle_keyp(int const keycode, void *ptr)
{
	static int		i = 0;
	t_handler const	*handler = (t_handler *)ptr;

	if (keycode == KEY_ESC)
		terminate_program(handler->conf, handler->mlxptr, handler->winptr);
	if (keycode == KEY_LEFT)
		mlx_put_image_to_window(handler->mlxptr, handler->winptr,
				get_camera(handler->conf, --i < 0 ? -i : i)->img, 0, 0);
	if (keycode == KEY_RIGHT)
		mlx_put_image_to_window(handler->mlxptr, handler->winptr,
				get_camera(handler->conf, ++i < 0 ? -i : i)->img, 0, 0);
	return (0);
}

static int	handle_x(void *ptr)
{
	t_handler const	*handler = (t_handler *)ptr;

	terminate_program(handler->conf, handler->mlxptr, handler->winptr);
	return (0);
}

static int	validate_args(int argc, char **argv)
{
	char	*dptr;

	if (argc != 2 && argc != 3)
		g_errno = EXEC_INV_ARG;
	else if (!(dptr = ft_strrchr(*(argv + 1), '.')) || ft_strcmp(".rt", dptr))
		g_errno = EXEC_INV_FNAME;
	else if (argc == 3 && ft_strcmp("--save", *(argv + 2)))
		g_errno = EXEC_INV_ARG;
	return (!g_errno);
}

int			main(int argc, char **argv)
{
	t_conf	conf;
	void	*mlxp;
	void	*winp;

	ft_bzero(&conf, sizeof(t_conf));
	if (!(mlxp = mlx_init()) || !validate_args(argc, argv) ||
			!read_config(&conf, *(argv + 1), mlxp) || g_errno)
	{
		print_error();
		terminate_program(&conf, mlxp, NULL);
	}
	render_cameras(conf.c, &conf);
	if (argc == 2)
	{
		if (!(winp = mlx_new_window(mlxp, conf.r.x, conf.r.y, "miniRT")))
			terminate_program(&conf, mlxp, NULL);
		mlx_put_image_to_window(mlxp, winp, conf.c->img, 0, 0);
		mlx_key_hook(winp, &handle_keyp, &(t_handler){&conf, mlxp, winp});
		mlx_hook(winp, 17, 0L, &handle_x, &(t_handler){&conf, mlxp, winp});
		mlx_loop(mlxp);
	}
	bmp_save(conf.r, conf.c, "screenshot.bmp");
	if (g_errno)
		print_error();
	terminate_program(&conf, mlxp, NULL);
}
