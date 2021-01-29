/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:27:48 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/29 19:52:42 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <libftmath.h>
#include <stdlib.h>

t_triangle	*create_triangle(t_conf *conf, char *str)
{
	t_triangle	tr;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 5 || ft_strcmp(*tab, "tr"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_TRIANGLE;
		return (NULL);
	}
	read_vec(tr.a, *(tab + 1), 0.0f, 0.0f);
	read_vec(tr.ab, *(tab + 2), 0.0f, 0.0f);
	read_vec(tr.ac, *(tab + 3), 0.0f, 0.0f);
	vec3_sub(tr.ab, tr.ab, tr.a);
	vec3_sub(tr.ac, tr.ac, tr.a);
	tr.color = read_color(*(tab + 4));
	tr.next = conf->tr;
	conf->tr = ft_memdup(&tr, sizeof(t_triangle));
	ft_split_free(tab);
	return (conf->tr);
}

t_triangle	*get_triangle(t_conf *conf, size_t index)
{
	size_t		count;
	t_triangle	*ret;

	count = 1;
	ret = conf->tr;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_triangles(t_conf *conf)
{
	t_triangle		*copy;

	while (conf->tr)
	{
		copy = conf->tr->next;
		free(conf->tr);
		conf->tr = copy;
	}
}
