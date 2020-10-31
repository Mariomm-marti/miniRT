/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:04:33 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/31 21:01:53 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <stdlib.h>

t_plane		*create_plane(t_conf *conf, char *str)
{
	t_plane		plane;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 4 || ft_strcmp(*tab, "pl"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_PLANE;
		return (NULL);
	}
	plane.loc = read_vec(*(tab + 1), 0.0f, 0.0f);
	plane.dir = read_vec(*(tab + 2), 0.0f, 1.0f);
	plane.color = read_color(*(tab + 3));
	plane.next = conf->pl;
	conf->pl = ft_memdup(&plane, sizeof(t_plane));
	ft_split_free(tab);
	return (conf->pl);
}

t_plane		*get_plane(t_conf *conf, size_t index)
{
	size_t		count;
	t_plane		*ret;

	count = 1;
	ret = conf->pl;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_planes(t_conf *conf)
{
	t_plane		*copy;

	while (conf->pl)
	{
		copy = conf->pl->next;
		free(conf->pl);
		conf->pl = copy;
	}
}
