/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 16:11:28 by mmartin-         ###   ########.fr       */
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

static int		intersect_planes(t_vec3 const loc,
		t_plane const *pl, t_ray *ray, int max)
{
	t_vec3	v;
	double	t;

	if (!pl || !max)
		return (0);
	t = vec3_dot(pl->dir, ray->ray);
	if (t < 0.000001f)
		return (0 + intersect_planes(loc, pl->next, ray, max - 1));
	vec3_sub(v, pl->loc, loc);
	t = vec3_dot(v, pl->dir) / t;
	if (t < 0 || t > ray->dist)
		return (0 + intersect_planes(loc, pl->next, ray, max - 1));
	vec3_mult(ray->point, ray->ray, t);
	vec3_add(ray->point, ray->point, loc);
	if (vec3_dot(ray->ray, pl->dir) < 0.0f)
		vec3_mult(ray->normal, pl->dir, -1);
	else
		ft_memcpy(ray->normal, pl->dir, sizeof(t_vec3));
	ray->color = pl->color;
	ray->dist = t;
	return (1 + intersect_planes(loc, pl->next, ray, max - 1));
}

static int		intersect_spheres(t_vec3 const loc,
		t_sphere const *sp, t_ray *ray, int max)
{
	t_vec3	pc;
	double	ppcr;
	double	dfn;

	if (!sp || !max)
		return (0);
	vec3_sub(pc, sp->loc, loc);
	ppcr = vec3_dot(pc, ray->ray);
	dfn = vec3_dot(pc, pc) - ppcr * ppcr;
	if (dfn > sp->radius * sp->radius)
		return (0 + intersect_spheres(loc, sp->next, ray, max - 1));
	dfn = sqrt(sp->radius * sp->radius - dfn);
	dfn = ppcr - dfn < ppcr + dfn && ppcr - dfn > 0 ? ppcr - dfn : ppcr + dfn;
	if (dfn > ray->dist || dfn <= 0)
		return (0 + intersect_spheres(loc, sp->next, ray, max - 1));
	vec3_mult(ray->point, ray->ray, dfn);
	vec3_add(ray->point, ray->point, loc);
	vec3_sub(ray->normal, ray->point, sp->loc);
	vec3_normalize(ray->normal, ray->normal);
	ray->dist = dfn;
	ray->color = sp->color;
	return (1 + intersect_spheres(loc, sp->next, ray, max - 1));
}

static int		intersect_triangles(t_vec3 const loc,
		t_triangle const *tr, t_ray *ray, int max)
{
	t_vec3	pv;
	t_vec3	tv;
	t_vec3	qv;
	double	det;

	if (!tr || !max)
		return (0);
	vec3_cross(pv, ray->ray, tr->ac);
	if (fabs(det = vec3_dot(tr->ab, pv)) < 0.000001f)
		return (0 + intersect_triangles(loc, tr->next, ray, max - 1));
	det = 1 / det;
	vec3_sub(tv, loc, tr->a);
	if ((pv[0] = vec3_dot(tv, pv) * det) < 0.0f || pv[0] > 1.0f)
		return (0 + intersect_triangles(loc, tr->next, ray, max - 1));
	vec3_cross(qv, tv, tr->ab);
	if ((pv[1] = vec3_dot(ray->ray, qv) * det) < 0.0f || pv[0] + pv[1] > 1.0f)
		return (0 + intersect_triangles(loc, tr->next, ray, max - 1));
	if ((pv[2] = vec3_dot(tr->ac, qv) * det) > ray->dist || pv[2] < 0)
		return (0 + intersect_triangles(loc, tr->next, ray, max - 1));
	if (vec3_dot(ray->ray, tr->normal) < 0.0f)
		vec3_mult(ray->normal, tr->normal, -1);
	else
		ft_memcpy(ray->normal, tr->normal, sizeof(t_vec3));
	vec3_mult(ray->point, ray->ray, pv[2]);
	vec3_add(ray->point, ray->point, loc);
	ray->dist = pv[2];
	ray->color = tr->color;
	return (1 + intersect_triangles(loc, tr->next, ray, max - 1));
}

//static void		solve_quadratic(double const a, double const b,
//		double const c, t_vec3 out)
//{
//	double	inv;
//	double	resqrt;
//	double	first;
//	double	second;
//
//	inv = 1 / (2 * a);
//	resqrt = sqrt(b * b - 4 * a * c);
//	first = (-b + resqrt) * inv;
//	second = (-b - resqrt) * inv;
//	out[0] = first < second ? first : second;
//	out[1] = first;
//	out[2] = second;
//}
//
//static int		intersect_cylinders(t_vec3 const loc,
//		t_cylinder const *cy, t_ray *ray, int max)
//{
//	t_vec3	co;
//	t_vec3	aside;
//	t_vec3	bside;
//	t_byte	is_render;
//
//	if (!cy || !max)
//		return (0);
//	is_render = 0;
//	vec3_mult(aside, cy->dir, vec3_dot(ray->ray, cy->dir));
//	vec3_sub(aside, ray->ray, aside);
//	vec3_sub(co, loc, cy->loc);
//	vec3_mult(bside, cy->dir, vec3_dot(co, cy->dir));
//	vec3_sub(bside, co, bside);
//	co[0] = vec3_dot(aside, aside);
//	co[1] = 2 * vec3_dot(aside, bside);
//	co[2] = vec3_dot(bside, bside) - cy->radius * cy->radius;
//	solve_quadratic(co[0], -co[1], co[2], co);
//	if (isnan(co[0]) || co[0] < 0 || co[0] > ray->dist)
//		return (0 + intersect_cylinders(loc, cy->next, ray, max - 1));
//	vec3_mult(aside, ray->ray, -co[1]);
//	vec3_add(aside, loc, aside);
//	vec3_mult(bside, cy->dir, cy->height);
//	vec3_add(bside, bside, cy->loc);
//	vec3_sub(bside, aside, bside);
//	vec3_sub(aside, aside, cy->loc);
//	if (vec3_dot(cy->dir, aside) > 0 && vec3_dot(cy->dir, bside) < 0)
//		is_render = 1;
//	vec3_mult(aside, ray->ray, -co[2]);
//	vec3_add(aside, loc, aside);
//	vec3_mult(bside, cy->dir, cy->height);
//	vec3_add(bside, bside, cy->loc);
//	vec3_sub(bside, aside, bside);
//	vec3_sub(aside, aside, cy->loc);
//	if (vec3_dot(cy->dir, aside) > 0 && vec3_dot(cy->dir, bside) < 0)
//		is_render = 2;
//	if (!is_render)
//		return (0 + intersect_cylinders(loc, cy->next, ray, max - 1));
//	vec3_mult(ray->point, ray->ray, is_render == 1 ? -co[1] : -co[2]);
//	vec3_add(ray->point, ray->point, loc);
//	vec3_sub(ray->normal, ray->point, cy->loc);
//	vec3_mult(ray->normal, cy->dir, vec3_dot(ray->normal, cy->dir));
//	vec3_add(ray->normal, ray->normal, cy->loc);
//	vec3_sub(ray->normal, ray->point, ray->normal);
//	vec3_normalize(ray->normal, ray->normal);
//	ray->dist = is_render == 1 ? co[1] : co[2];
//	ray->color = cy->color;
//	return (1 + intersect_cylinders(loc, cy->next, ray, max - 1));
//}

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

static t_color	shadow_ray(t_conf const *conf,
		t_light const *l, t_ray *ray)
{
	t_ray		shadow;
	t_vec3		normal;
	t_color		result;
	double		lamb;

	result = add_color(0, conf->a.color, conf->a.ratio);
	vec3_mult(normal, ray->normal, -0.001);
	vec3_add(ray->point, normal, ray->point);
	while (l)
	{
		vec3_sub(shadow.ray, l->loc, ray->point);
		vec3_normalize(shadow.ray, shadow.ray);
		shadow.dist = INFINITY;
		intersect_planes(ray->point, conf->pl, &shadow, 1);
		intersect_spheres(ray->point, conf->sp, &shadow, 1);
		intersect_triangles(ray->point, conf->tr, &shadow, 1);
		if (shadow.dist != INFINITY &&
				(lamb = vec3_dot(shadow.ray, ray->normal)) >= 0.0f)
			result = add_color(result, l->color, lamb);
		l = l->next;
	}
	return (mult_color(result, ray->color, 1.0f));
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
//				intersect_cylinders(cam->loc, conf->cy, &ray, -1);
				if (ray.dist != INFINITY)
					*((unsigned int *)((char *)cam->grid + (y * cam->sline +
									x * (cam->bpp) / 8))) = /*ray.color;*/shadow_ray(conf, conf->l, &ray);
			}
		cam = cam->next;
	}
}
