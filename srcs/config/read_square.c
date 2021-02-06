/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 22:35:12 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/06 17:29:47 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <libftmath.h>
#include <stdlib.h>

static void	tesselate_square(t_conf *conf, t_square const *sq)
{
	t_triangle	tr;
	t_vec3		v[4];
	double		h;

	h = sq->radius * SQRT2 / 2;
	vec3_cross(tr.a, (t_vec3){-0.7071f, 0.7071, 0.0f}, sq->dir);
	vec3_mult(tr.ac, tr.a, h);
	vec3_add(v[0], sq->loc, tr.ac);
	vec3_sub(v[2], sq->loc, tr.ac);
	vec3_cross(tr.ab, tr.a, sq->dir);
	vec3_mult(tr.ac, tr.ab, h);
	vec3_add(v[3], sq->loc, tr.ac);
	vec3_sub(v[1], sq->loc, tr.ac);
	ft_memcpy(tr.a, v[0], sizeof(t_vec3));
	vec3_sub(tr.ab, tr.a, v[1]);
	vec3_sub(tr.ac, tr.a, v[2]);
	tr.color = sq->color;
	tr.next = conf->tr;
	conf->tr = ft_memdup(&tr, sizeof(t_triangle));
	vec3_sub(tr.ab, tr.a, v[2]);
	vec3_sub(tr.ac, tr.a, v[3]);
	tr.next = conf->tr;
	conf->tr = ft_memdup(&tr, sizeof(t_triangle));
}

void		create_square(t_conf *conf, char *str)
{
	t_square	square;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return ;
	if (ft_split_count(tab) != 5 || ft_strcmp(*tab, "sq"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_SQUARE;
		return ;
	}
	read_vec(square.loc, *(tab + 1), 0.0f, 0.0f);
	read_vec(square.dir, *(tab + 2), -1.0f, 1.0f);
	vec3_normalize(square.dir, square.dir);
	if ((square.radius = read_val(*(tab + 3), 0)) < 0.1f)
		g_errno = CONF_INV_SQUARE;
	square.color = read_color(*(tab + 4));
	tesselate_square(conf, &square);
	ft_split_free(tab);
}
