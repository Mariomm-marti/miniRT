/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:49:49 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 20:24:48 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>
#include <libftmath.h>
#include <libft.h>

int	intersect_triangles(t_vec3 const loc,
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
	vec3_mult(ray->normal,
			tr->normal, vec3_dot(ray->ray, tr->normal) < 0.0f ? -1 : 1);
	vec3_mult(ray->point, ray->ray, (ray->dist = pv[2]));
	vec3_add(ray->point, ray->point, loc);
	ray->color = tr->color;
	return (1 + intersect_triangles(loc, tr->next, ray, max - 1));
}
