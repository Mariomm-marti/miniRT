/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/24 20:42:23 by mmartin-         ###   ########.fr       */
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
		t_vec3 const holy_vector, t_res const *pixel)
{
	vec3_mult(ray, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, pixel->x);
	vec3_add(ray, (t_vec3){-ctw[1][0] * pixel->y,
			-ctw[1][1] * pixel->y,
			-ctw[1][2] * pixel->y}, ray);
	vec3_add(ray, holy_vector, ray);
	vec3_normalize(ray, ray);
}

static t_sphere	*intersect_sphere(t_sphere const *sp,
		t_camera const *cam, t_ray *ray)
{
	t_vec3 register	vec_origsp;
	double register	proj_origsp;
	double register	proj_intsp;
	double register	close_inter;

	vec3_sub(vec_origsp, sp->loc, cam->loc);
	proj_origsp = vec3_dot(vec_origsp, ray->ray);
	if (proj_origsp < 0.0f)
		return (NULL);
	proj_intsp = vec3_dot(vec_origsp, vec_origsp);
	proj_intsp -= proj_origsp * proj_origsp;
	if (proj_intsp > sp->radius * sp->radius)
		return (NULL);
	proj_intsp = sqrt(sp->radius * sp->radius - proj_intsp);
	if (proj_origsp - proj_intsp < 0 && proj_origsp + proj_intsp < 0)
		return (NULL);
	if((close_inter = proj_origsp + proj_intsp) > proj_origsp - proj_intsp)
		close_inter = proj_origsp - proj_intsp;
	if (close_inter < ray->dist)
	{
		ray->dist = close_inter;
		ray->color = sp->color;
		return ((t_sphere *)sp);
	}
	return (NULL);
}

static void		render_camera(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_ray			ray;
	t_res			pixel;

	ft_bzero(&ray, sizeof(t_ray));
	ray.dist = INFINITY;
	lookat(ctw, cam->loc, cam->dir);
	ray_generic(ray.holy_vector, &(conf->r), ctw, cam->fov);
	pixel = (t_res){.x = 0, .y = 0};
	while (pixel.x < conf->r.x)
	{
		while (pixel.y < conf->r.y)
		{
			ray_specific(ctw, ray.ray, ray.holy_vector, &pixel);
			if (intersect_sphere(conf->sp, cam, &ray))
				*(cam->grid + (pixel.y * cam->sline + pixel.x * (cam->bpp / 8))) = ray.color;
			pixel.y++;
		}
		pixel.x++;
	}
}

void		render_cameras(t_conf const *conf)
{
	t_camera	*cur;

	cur = conf->c;
	while (cur)
	{
		render_camera(cur, conf);
		cur = cur->next;
	}
}
