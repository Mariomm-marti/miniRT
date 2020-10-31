/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 03:59:02 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/31 21:01:58 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <stdlib.h>

t_sphere	*create_sphere(t_conf *conf, char *str)
{
	t_sphere	sphere;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 4 || ft_strcmp(*tab, "sp"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_SPHERE;
		return (NULL);
	}
	sphere.loc = read_vec(*(tab + 1), 0.0f, 0.0f);
	if ((sphere.diameter = read_val(*(tab + 2), 0)) < 0.1)
		g_errno = CONF_INV_SPHERE;
	sphere.color = read_color(*(tab + 3));
	sphere.next = conf->sp;
	conf->sp = ft_memdup(&sphere, sizeof(t_sphere));
	ft_split_free(tab);
	return (conf->sp);
}

t_sphere	*get_sphere(t_conf *conf, size_t index)
{
	size_t		count;
	t_sphere	*ret;

	count = 1;
	ret = conf->sp;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_spheres(t_conf *conf)
{
	t_sphere	*copy;

	while (conf->sp)
	{
		copy = conf->sp->next;
		free(conf->sp);
		conf->sp = copy;
	}
}
