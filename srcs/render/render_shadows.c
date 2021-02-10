/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:44:21 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/10 20:00:50 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <math.h>

static t_color	add_color(t_color const a, t_color const b, double ratio)
{
	t_color		result;
	t_color		ar;
	t_color		br;

	ar = a >> 16 & 255;
	br = (int)((b >> 16 & 255) * ratio);
	result = (ar + br > 255 ? 255 : ar + br) << 16;
	ar = a >> 8 & 255;
	br = (int)((b >> 8 & 255) * ratio);
	result |= (ar + br > 255 ? 255 : ar + br) << 8;
	ar = a & 255;
	br = (int)((b & 255) * ratio);
	result |= (ar + br > 255 ? 255 : ar + br);
	return (result);
}

static t_color	mult_color(t_color const a, t_color const b, double ratio)
{
	return ((int)((a >> 16 & 255) * (b >> 16 & 255) * ratio / 255) << 16 |
			(int)((a >> 8 & 255) * (b >> 8 & 255) * ratio / 255) << 8 |
			(int)((a & 255) * (b & 255) * ratio / 255));
}

t_color			shadow_ray(t_conf const *conf,
		t_light const *l, t_ray *ray)
{
	t_ray		shadow;
	t_vec3		acne;
	t_color		result;
	double		lamb;

	vec3_mult(acne, ray->normal, 0.001f);
	vec3_add(ray->point, acne, ray->point);
	result = add_color(0, conf->a.color, conf->a.ratio);
	while (l)
	{
		vec3_sub(shadow.ray, l->loc, ray->point);
		vec3_normalize(shadow.ray, shadow.ray);
		shadow.dist = INFINITY;
		intersect_planes(ray->point, conf->pl, &shadow, 1);
		intersect_spheres(ray->point, conf->sp, &shadow, 1);
		intersect_triangles(ray->point, conf->tr, &shadow, 1);
		intersect_cylinders(ray->point, conf->cy, &shadow, 1);
		if (shadow.dist == INFINITY &&
				(lamb = vec3_dot(shadow.ray, ray->normal)) >= 0.0f)
			result = add_color(result, l->color, lamb * l->ratio);
		l = l->next;
	}
	return (mult_color(result, ray->color, 1.0f));
}
