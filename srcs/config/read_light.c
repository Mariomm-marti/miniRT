/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:23:28 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/27 22:32:53 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libft.h>
#include <stdlib.h>

int			create_light(t_conf *conf, char *str)
{
	t_light		light;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (0);
	if (ft_split_count(tab) != 4 || ft_strcmp(*tab, "l"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_FMT;
		return (0);
	}
	light.loc = read_vec(*(tab + 1), 0.0f, 0.0f);
	light.ratio = read_val(*(tab + 2), 0);
	light.color = read_color(*(tab + 3));
	ligh.next = conf->l;
	conf->l = ft_memdup(&light, sizeof(t_light));
	ft_split_free(tab);
	return (1);
}

t_light		*get_light(t_conf *conf, size_t index)
{
	size_t		count;
	t_light		*ret;

	count = 1;
	ret = conf->l;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_lights(t_conf *conf)
{
	t_light	*copy;

	while (conf->l)
	{
		copy = conf->l->next;
		free(conf->l);
		conf->l = copy;
	}
}