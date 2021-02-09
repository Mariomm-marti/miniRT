/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_planes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:46:43 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 20:10:12 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>
#include <libft.h>
#include <libftmath.h>

int	intersect_planes(t_vec3 const loc,
		t_plane const *pl, t_ray *ray, int max)
{
	t_vec3	v;
	double	t;

	if (!pl || !max)
		return (0);
	t = vec3_dot(pl->dir, ray->ray);
	if (fabs(t) < 0.000001f)
		return (0 + intersect_planes(loc, pl->next, ray, max - 1));
	vec3_sub(v, pl->loc, loc);
	t = vec3_dot(v, pl->dir) / t;
	if (t < 0 || t > ray->dist)
		return (0 + intersect_planes(loc, pl->next, ray, max - 1));
	if (vec3_dot(ray->ray, pl->dir) > 0.0f)
		vec3_mult(ray->normal, pl->dir, -1);
	else
		ft_memcpy(ray->normal, pl->dir, sizeof(t_vec3));
	vec3_mult(ray->point, ray->ray, t);
	vec3_add(ray->point, ray->point, loc);
	ray->dist = t;
	ray->color = pl->color;
	return (1 + intersect_planes(loc, pl->next, ray, max - 1));
}
