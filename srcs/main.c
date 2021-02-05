/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:18:44 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/05 13:03:14 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/config.h"
#include <fcntl.h>
#include <unistd.h>
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

static int	bmp_save(t_res const res, t_camera const *cam, char const *p)
{
	char			buff[54];
	long long int	t;
	int				fd;
	char			padding;

	if ((fd = open(p, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0600)) == -1)
		return (!!(g_errno = BMP_INV_OPEN));
	ft_bzero(buff, 54);
	ft_memcpy(buff, "BM", 2);
	t = 0x2800000036ULL;
	ft_memcpy(buff + 10, &t, 8);
	ft_memcpy(buff + 18, &res.x, 2);
	ft_memcpy(buff + 22, &res.y, 2);
	t = 0x200001ULL;
	ft_memcpy(buff + 26, &t, 4);
	write(fd, buff, 54);
	padding = (cam->bpp - cam->sline % (cam->bpp / 8)) % (cam->bpp / 8);
	t = res.y;
	while (--t >= 0)
	{
		write(fd, (cam->grid + (t * cam->sline)), res.x * (cam->bpp / 8));
		write(fd, (t_vec3){0, 0, 0}, padding);
	}
	return (close(fd));
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
