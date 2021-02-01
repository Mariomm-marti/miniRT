/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/01 20:45:21 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h> //
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

static int		intersect_planes(t_camera const *cam,
		t_plane const *pl, t_ray *ray)
{
	double	t;
	t_vec3	v;

	if (!pl)
		return (0);
	vec3_sub(v, cam->loc, pl->loc);
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
	double	dfn;

	if (!sp)
		return (0);
	vec3_sub(pc, cam->loc, sp->loc);
	ppcr = vec3_dot(pc, ray->ray);
	dfn = vec3_dot(pc, pc) - ppcr * ppcr;
	if (dfn > sp->radius * sp->radius)
		return (0 + intersect_spheres(cam, sp->next, ray));
	dfn = sqrt(sp->radius * sp->radius - dfn);
	dfn = ppcr - dfn < ppcr + dfn && ppcr - dfn > 0 ? ppcr - dfn : ppcr + dfn;
	if (dfn > ray->dist || dfn <= 0)
		return (0 + intersect_spheres(cam, sp->next, ray));
	ray->dist = dfn;
	ray->color = sp->color;
	return (1 + intersect_spheres(cam, sp->next, ray));
}

static int		intersect_triangles(t_camera const *cam,
		t_triangle const *tr, t_ray *ray)
{
	t_vec3	pv;
	t_vec3	tv;
	t_vec3	qv;
	double	det;

	if (!tr)
		return (0);
	vec3_cross(pv, ray->ray, tr->ac);
	if (fabs(det = vec3_dot(tr->ab, pv)) < 0.000001f)
		return (0 + intersect_triangles(cam, tr->next, ray));
	det = 1 / det;
	vec3_sub(tv, tr->a, cam->loc);
	if ((pv[0] = vec3_dot(tv, pv) * det) < 0.0f || pv[0] > 1.0f)
		return (0 + intersect_triangles(cam, tr->next, ray));
	vec3_cross(qv, tv, tr->ab);
	if ((pv[1] = vec3_dot(ray->ray, qv) * det) < 0.0f || pv[0] + pv[1] > 1.0f)
		return (0 + intersect_triangles(cam, tr->next, ray));
	if ((pv[2] = vec3_dot(tr->ac, qv) * det) > ray->dist || pv[2] < 0)
		return (0 + intersect_triangles(cam, tr->next, ray));
	ray->dist = pv[2];
	ray->color = tr->color;
	return (1 + intersect_triangles(cam, tr->next, ray));
}

void			render_cameras(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_ray			ray;
	unsigned short	x;
	unsigned short	y;

	lookat(ctw, cam->loc, cam->dir);
	ray_generic(ray.holy_vector, &(conf->r), ctw, cam->fov);
	while (cam && (x = -1))
	{
		while (++x < conf->r.x && (y = -1))
			while (++y < conf->r.y)
			{
				ray.dist = INFINITY;
				ray_specific(ctw, &ray, x, y);
				intersect_planes(cam, conf->pl, &ray);
				intersect_spheres(cam, conf->sp, &ray);
				intersect_triangles(cam, conf->tr, &ray);
				if (ray.dist != INFINITY)
					*((unsigned int *)((char *) cam->grid + (y * cam->sline + x * (cam->bpp) / 8))) = ray.color;
			}
		cam = cam->next;
	}
}
