/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:30:08 by mortega-          #+#    #+#             */
/*   Updated: 2021/02/04 16:53:25 by mortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>

char	fill_cylinder(char *line, t_list **cylinder)
{
	char		**params;
	t_cylinder	*cl;
	t_list		*new;

	params = ft_split(line, ' ');
	*params == NULL ? ft_exit_err(MCE) : 0;
	cl = (t_cylinder *)malloc(sizeof(*cl));
	fill_vector(params[0], &cl->center);
	fill_vector(params[1], &cl->vector);
	cl->radius = ft_atof(params[2]) / 2;
	cl->height = ft_atof(params[3]);
	fill_rgb(params[4], &cl->rgb);
	new = ft_lstnew(cl);
	ft_lstadd_front(cylinder, new);
	ft_split_count(line, ' ') != 5 ? ft_exit_err(WNP) : 0;
	ft_split_free(params);
	if (cl->vector.x > 1 || cl->vector.y > 1 || cl->vector.z > 1 ||
			cl->vector.x < -1 || cl->vector.y < -1 || cl->vector.z < -1)
		ft_exit_err(VEC);
	cl->radius < 0 || cl->height < 0 ? ft_exit_err(NVY) : 0;
	return (0);
}

float	intersect_cylinder(t_cylinder *cyl, t_vector origin, t_vector dir)
{
	t_vector	p[4];
	t_point		q1;
	float		a[3];
	float		t[2];

	p[1] = ft_minusvector(dir,
			ft_scalarproduct(ft_dotproduct(dir, cyl->vector), cyl->vector));
	p[2] = ft_minusvector(ft_minusvector(origin, cyl->center),
			ft_scalarproduct(ft_dotproduct(ft_minusvector(origin,
						cyl->center), cyl->vector), cyl->vector));
	a[0] = ft_dotproduct(p[1], p[1]);
	a[1] = 2 * ft_dotproduct(p[1], p[2]);
	a[2] = ft_dotproduct(p[2], p[2]) - (cyl->radius * cyl->radius);
	t[0] = (-a[1] + sqrt(a[1] * a[1] - 4 * a[0] * a[2])) / (2 * a[0]);
	t[1] = (-a[1] - sqrt(a[1] * a[1] - 4 * a[0] * a[2])) / (2 * a[0]);
	p[1] = ft_sumvector(cyl->center,
			ft_scalarproduct(cyl->height, cyl->vector));
	p[2] = ft_minusvector(cyl->center,
			ft_scalarproduct(cyl->height, cyl->vector));
	t[0] = t[0] < t[1] && t[0] > 0 ? t[0] : t[1];
	q1 = ft_sumvector(origin, ft_scalarproduct(t[0], dir));
	a[0] = ft_dotproduct(cyl->vector, ft_minusvector(q1, p[1]));
	a[1] = ft_dotproduct(cyl->vector, ft_minusvector(q1, p[2]));
	return (a[0] < 0 && a[1] > 0 ? t[0] : -1);
}

/*
**	ft_normalize(&cyl->vector);
**	t_vector l = ft_minusvector(origin, cyl->center);
**	float	d = fabsf(ft_dotproduct(l, cyl->vector));
**	ft_normalize(&dir);
**	float	k = fabsf(ft_dotproduct(dir, cyl->vector));
**	float	m = cyl->height - d;
**	if (m < 0) return -1;
**	float	t0 = m / k;
**	t_point	P = ft_sumvector(origin, ft_scalarproduct(t0, dir));
**	float dst = ft_modulevector(ft_minusvector(P, cyl->center));
**	t_point	O = ft_sumvector(cyl->center, ft_scalarproduct(dst, cyl->vector));
**	float dist = ft_modulevector(ft_minusvector(P, O));
**	//printf("Comprobar:\n\tl(%f,%f,%f)\n\td = %f\n\tk = %f\n\tm = %f\n\tt0 = %f\n\tP(%f,%f,%f)\n\tO(%f,%f,%f)\n\tdist = %f\n", l.x, l.y, l.z, d, k, m, t0, P.x, P.y, P.z, O.x, O.y, O.z, dist);
**	//if (P.z < 1.1)
**	//	exit(EXIT_FAILURE);
**	//printf("\tdir(%f,%f,%f)\n", dir.x, dir.y, dir.z);
**	return (dist <= cyl->radius ? t0 : -1);
*/

void	rens_cylinder(t_cylinder *c, t_vector ori, t_vector dir, t_hitobj *obj)
{
	float t0;

	if ((t0 = intersect_cylinder(c, ori, dir)) > 0)
		if (t0 < obj->near)
		{
			obj->near = t0;
			obj->color = c->rgb;
		}
}
