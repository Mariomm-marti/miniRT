/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:12:43 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/05 00:12:03 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <libft.h>
#include <fcntl.h>

int						bmp_save(t_res const res,
		t_camera const *cam, char const *p)
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
