/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:12:43 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/04 20:53:00 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <libft.h>
#include <fcntl.h>

int						bmp_save(t_res const resolution,
		t_camera const *cam, char const *p)
{
	char					buff[resolution.x];
	long long int			t;
	int						u;
	int						fd;

	if ((fd = open(p, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0600)) == -1)
		return (!!(g_errno = BMP_INV_OPEN));
	ft_bzero(buff, resolution.x);
	ft_memcpy(buff, "BM", 2);
	t = 0x2800000036ULL;
	ft_memcpy(buff + 10, &t, 8);
	ft_memcpy(buff + 18, &resolution.x, 2);
	ft_memcpy(buff + 22, &resolution.y, 2);
	t = 0x200001ULL;
	ft_memcpy(buff + 26, &t, 4);
	write(fd, buff, 54);
	t = resolution.y;
	while (--t && (u = -1))
	{
		while (++u < resolution.x)
			buff[u] = *(t_color *)(cam->grid +
					(t * cam->sline + (u * (cam->bpp / 8))));
		write(fd, &buff, resolution.x);
	}
	return (close(fd));
}
