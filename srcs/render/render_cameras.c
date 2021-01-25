/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/25 20:48:31 by mmartin-         ###   ########.fr       */
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

static t_bool	intersect_plane(t_camera const *cam,
		t_plane const *plane, t_ray *ray)
{
	double	det;
	double	t;
	t_vec3	planenormal;
	t_vec3	planeray;

	vec3_normalize(planenormal, plane->dir);
	det = vec3_dot(planenormal, ray->ray);
	if (det == 0.0f)
		return (0);
	vec3_sub(planeray, plane->loc, cam->loc);
	if ((t = vec3_dot(planeray, plane->dir) / det) < 0)
		return (0);
	if (t < ray->dist)
	{
		ray->dist = t;
		ray->color = plane->color;
	}
	return (1);
}

static t_bool	intersect_planes(t_camera const *cam,
		t_plane const *plane, t_ray *ray)
{
	t_bool	ret;

	ret = 0;
	while (plane)
	{
		ret |= intersect_plane(cam, plane, ray);
		plane = plane->next;
	}
	return (ret);
}

void			render_cameras(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_ray			ray;
	unsigned short	x;
	unsigned short	y;

	lookat(ctw, cam->loc, cam->dir);
	ray.dist = INFINITY;
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
				if (intersect_planes(cam, conf->pl, &ray))
				{
					*((unsigned int *)((char *) cam->grid + (y * cam->sline + x * (cam->bpp) / 8))) = ray.color;
					printf("Intersected ray %lf %lf %lf", ray.ray[0], ray.ray[1], ray.ray[2]);
				}
				y++;
			}
			x++;
		}
		cam = cam->next;
	}
}
