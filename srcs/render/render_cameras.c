/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 20:12:44 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <math.h>

static void		ray_generic(t_vec3 g, t_res const *dim,
		t_mat44 const ctw, t_byte const fov)
{
	t_vec3	t;

	vec3_mult(g, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, -dim->x / 2);
	vec3_mult(t, (t_vec3){ctw[1][0], ctw[1][1], ctw[1][2]}, dim->y / 2);
	vec3_add(g, g, t);
	vec3_mult(t, (t_vec3){ctw[2][0], ctw[2][1], ctw[2][2]},
			dim->y / (2 * tan(fov * DEG_RAD * 0.5)));
	vec3_sub(g, g, t);
}

static void		ray_specific(t_mat44 const ctw, t_ray *ray,
		unsigned int const x, unsigned int const y)
{
	vec3_mult(ray->ray, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, x);
	vec3_add(ray->ray, (t_vec3){-ctw[1][0] * y,
			-ctw[1][1] * y,
			-ctw[1][2] * y}, ray->ray);
	vec3_add(ray->ray, ray->holy_vector, ray->ray);
	vec3_normalize(ray->ray, ray->ray);
}

void			render_cameras(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_ray			ray;
	unsigned short	x;
	unsigned short	y;

	while (cam && (x = -1))
	{
		lookat(ctw, cam->loc, cam->dir);
		ray_generic(ray.holy_vector, &(conf->r), ctw, cam->fov);
		while (++x < conf->r.x && (y = -1))
			while (++y < conf->r.y)
			{
				ray.dist = INFINITY;
				ray_specific(ctw, &ray, x, y);
				intersect_planes(cam->loc, conf->pl, &ray, -1);
				intersect_spheres(cam->loc, conf->sp, &ray, -1);
				intersect_triangles(cam->loc, conf->tr, &ray, -1);
				intersect_cylinders(cam->loc, conf->cy, &ray, -1);
				if (ray.dist != INFINITY)
					*((unsigned int *)((char *)cam->grid + (y * cam->sline +
						x * (cam->bpp) / 8))) = shadow_ray(conf, conf->l, &ray);
			}
		cam = cam->next;
	}
}
