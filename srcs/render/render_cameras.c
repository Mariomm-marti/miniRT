/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/26 19:21:02 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdlib.h> //
#include <stdio.h> //
#include <libftmath.h>
#include <math.h>

static void		ray_generic(t_vec3 g, t_res const *dim,
		t_mat44 const ctw, t_byte const fov)
{
	t_vec3	t;

	vec3_mult(g, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, -dim->x / 2);
	vec3_mult(t, (t_vec3){ctw[1][0], ctw[1][1], ctw[1][2]}, dim->y / 2);
	vec3_add(g, t, g);
	vec3_mult(t, (t_vec3){ctw[2][0], ctw[2][1], ctw[2][2]},
			dim->y / (2 * tan(fov * DEG_RAD * 0.5)));
	vec3_sub(g, g, t);
}

static void		ray_specific(t_mat44 const ctw, t_vec3 ray,
		t_vec3 const holy_vector, unsigned int const x, unsigned int const y)
{
	vec3_mult(ray, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, x);
	vec3_add(ray, (t_vec3){-ctw[1][0] * y,
			-ctw[1][1] * y,
			-ctw[1][2] * y}, ray);
	vec3_add(ray, holy_vector, ray);
	vec3_normalize(ray, ray);
}

static int		intersect_planes(t_camera const *cam,
		t_plane const *pl, t_ray *ray)
{
	double	t;
	t_vec3	v;

	if (!pl)
		return (0);
	vec3_sub(v, pl->loc, cam->loc);
	t = vec3_dot(v, pl->dir) / vec3_dot(ray->ray, pl->dir);
	if (t < 0.000001f || t > ray->dist)
		return (0 + intersect_planes(cam, pl->next, ray));
	ray->dist = t;
	ray->color = pl->color;
	return (1 + intersect_planes(cam, pl->next, ray));
}

static int		intersect_spheres(t_camera const *cam,
		t_sphere const *sp, t_ray *ray)
{
	t_vec3	pc;
	double	ppcr;
	double	dpc;
	double	delfin;
	double	seg;
	double	t;

	vec3_sub(pc, sp->loc, cam->loc);
	ppcr = vec3_dot(pc, ray->ray);
	dpc = vec3_dot(pc, pc); // squared, sqrt(dpc) == len
	delfin = dpc - ppcr * ppcr;
	if (delfin > sp->radius * sp->radius)
		return (0);
	seg = sqrt(sp->radius * sp->radius - delfin);
	t = ppcr - seg < ppcr + seg && ppcr - seg > 0 ? ppcr - seg : ppcr + seg;
	if (t > ray->dist || t <= 0)
		return (0);
	ray->dist = t;
	ray->color = sp->color;
	return (1);
}

void			render_cameras(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_ray			ray;
	unsigned short	x;
	unsigned short	y;

	lookat(ctw, cam->loc, cam->dir);
	ray_generic(ray.holy_vector, &(conf->r), ctw, cam->fov);
	while (cam)
	{
		x = 0;
		while (x < conf->r.x)
		{
			y = 0;
			while (y < conf->r.y)
			{
				ray.dist = INFINITY;
				ray_specific(ctw, ray.ray, ray.holy_vector, x, y);
				intersect_planes(cam, conf->pl, &ray);
				intersect_spheres(cam, conf->sp, &ray);
				if (ray.dist != INFINITY)
					*((unsigned int *)((char *) cam->grid + (y * cam->sline + x * (cam->bpp) / 8))) = ray.color;
				y++;
			}
			x++;
		}
		cam = cam->next;
	}
}
