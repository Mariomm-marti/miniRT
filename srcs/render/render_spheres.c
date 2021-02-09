/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spheres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:48:38 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/09 20:10:32 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>
#include <libft.h>
#include <libftmath.h>

int	intersect_spheres(t_vec3 const loc,
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
