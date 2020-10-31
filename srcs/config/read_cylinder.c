/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:33:38 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/31 21:01:45 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <stdlib.h>

t_cylinder	*create_cylinder(t_conf *conf, char *str)
{
	t_cylinder	cyl;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 6 || ft_strcmp(*tab, "cy"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_CYLINDER;
		return (NULL);
	}
	cyl.loc = read_vec(*(tab + 1), 0.0f, 0.0f);
	cyl.dir = read_vec(*(tab + 2), 0.0f, 1.0f);
	if ((cyl.diameter = read_val(*(tab + 3), 0)) < 0.1f)
		g_errno = CONF_INV_NUM;
	if ((cyl.height = read_val(*(tab + 4), 0)) < 0.1f)
		g_errno = CONF_INV_NUM;
	cyl.color = read_color(*(tab + 5));
	cyl.next = conf->cy;
	conf->cy = ft_memdup(&cyl, sizeof(t_cylinder));
	ft_split_free(tab);
	return (conf->cy);
}

t_cylinder	*get_cylinder(t_conf *conf, size_t index)
{
	size_t		count;
	t_cylinder	*ret;

	count = 1;
	ret = conf->cy;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_cylinders(t_conf *conf)
{
	t_cylinder	*copy;

	while (conf->cy)
	{
		copy = conf->cy->next;
		free(conf->cy);
		conf->cy = copy;
	}
}
