/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/21 20:04:00 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <mlx.h>

static t_color	render_pixel(t_vec3 const orig, t_vec3 const dest, t_conf const *conf)
{
}

static void		render_camera(t_camera const *cam, t_conf const *conf)
{

}


// TODO Multithreading can be implemented here
void		render_cameras(t_conf const *conf, void *mlxptr)
{
	t_camera	*cur;

	cur = conf->c;
	while (cur)
	{
		render_camera(cur, conf);
		cur = cur->next;
	}
}
