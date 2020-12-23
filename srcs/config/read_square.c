/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 22:35:12 by mmartin-          #+#    #+#             */
/*   Updated: 2020/12/23 22:49:51 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/config.h"
#include <libft.h>
#include <stdlib.h>

t_square	*create_square(t_conf *conf, char *str)
{
	t_square	square;
	char		**tab;

	if (!(tab = ft_split(str, ' ')))
		return (NULL);
	if (ft_split_count(tab) != 5 || ft_strcmp(*tab, "sq"))
	{
		ft_split_free(tab);
		g_errno = CONF_INV_SQUARE;
		return (NULL);
	}
	read_vec(square.loc, *(tab + 1), 0.0f, 0.0f);
	read_vec(square.dir, *(tab + 2), 0.0f, 1.0f);
	if ((square.side_size = read_val(*(tab + 3), 0)) < 0.1f)
		g_errno = CONF_INV_SQUARE;
	square.color = read_color(*(tab + 4));
	square.next = conf->sq;
	conf->sq = ft_memdup(&square, sizeof(t_square));
	ft_split_free(tab);
	return (conf->sq);
}

t_square	*get_square(t_conf *conf, size_t index)
{
	size_t		count;
	t_square	*ret;

	count = 1;
	ret = conf->sq;
	while (count <= index && ret)
	{
		ret = ret->next;
		count++;
	}
	return (ret);
}

void		free_squares(t_conf *conf)
{
	t_square	*copy;

	while (conf->sq)
	{
		copy = conf->sq->next;
		free(conf->sq);
		conf->sq = copy;
	}
}
