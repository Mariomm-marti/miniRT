/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:16:55 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 20:11:32 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>
#include <libft.h>
#include <libftmath.h>

static void		solve_quadratic(double const a, double const b,
		double const c, t_vec3 out)
{
	double	inv;
	double	resqrt;
	double	first;
	double	second;

	inv = 1 / (2 * a);
	resqrt = sqrt(b * b - 4 * a * c);
	first = (-b + resqrt) * inv;
	second = (-b - resqrt) * inv;
	out[0] = first < second && first > 0 ? first : second;
	out[1] = first;
	out[2] = second;
}

static void		solve_coefficients(t_vec3 const loc,
		t_cylinder const *cy, t_ray *ray, t_vec3 co)
{
	t_vec3	aside;
	t_vec3	bside;

	vec3_mult(aside, cy->dir, vec3_dot(ray->ray, cy->dir));
	vec3_sub(aside, ray->ray, aside);
	vec3_sub(co, loc, cy->loc);
	vec3_mult(bside, cy->dir, vec3_dot(co, cy->dir));
	vec3_sub(bside, co, bside);
	co[0] = vec3_dot(aside, aside);
	co[1] = 2 * vec3_dot(aside, bside);
	co[2] = vec3_dot(bside, bside) - cy->radius * cy->radius;
	solve_quadratic(co[0], co[1], co[2], co);
}

static int		resolve_intersection(t_vec3 const loc, t_ray const *ray,
		t_cylinder const *cy, double const coefficient)
{
	t_vec3	aside;
	t_vec3	bside;

	vec3_mult(aside, ray->ray, coefficient);
	vec3_add(aside, loc, aside);
	vec3_mult(bside, cy->dir, cy->height);
	vec3_add(bside, bside, cy->loc);
	vec3_sub(bside, aside, bside);
	vec3_sub(aside, aside, cy->loc);
	return (vec3_dot(cy->dir, aside) > 0 && vec3_dot(cy->dir, bside) < 0);
}

int				intersect_cylinders(t_vec3 const loc,
		t_cylinder const *cy, t_ray *ray, int max)
{
	t_vec3	co;
	t_byte	is_render;

	if (!cy || !max)
		return (0);
	solve_coefficients(loc, cy, ray, co);
	if (isnan(co[0]) || co[0] < 0 || co[0] > ray->dist)
		return (0 + intersect_cylinders(loc, cy->next, ray, max - 1));
	is_render = resolve_intersection(loc, ray, cy, co[1]);
	is_render += resolve_intersection(loc, ray, cy, co[2]);
	if (!is_render)
		return (0 + intersect_cylinders(loc, cy->next, ray, max - 1));
	vec3_mult(ray->point, ray->ray, is_render == 1 ? co[1] : co[2]);
	vec3_add(ray->point, ray->point, loc);
	vec3_sub(ray->normal, ray->point, cy->loc);
	vec3_mult(ray->normal, cy->dir, vec3_dot(ray->normal, cy->dir));
	vec3_add(ray->normal, ray->normal, cy->loc);
	vec3_sub(ray->normal, ray->point, ray->normal);
	vec3_normalize(ray->normal, ray->normal);
	ray->dist = is_render == 1 ? co[1] : co[2];
	ray->color = cy->color;
	return (1 + intersect_cylinders(loc, cy->next, ray, max - 1));
}
