/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/24 01:36:43 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>
#include <libftmath.h>
#include <math.h>

static void		ray_generic(t_vec3 g, t_res const *dim,
		t_mat44 const ctw, t_byte const fov)
{
	t_vec3	t;

	vec3_mult(g, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, -dim->x / 2);
	vec3_mult(t, (t_vec3){ctw[1][0], ctw[0][1], ctw[0][2]}, dime->y / 2);
	vec3_add(g, t, g);
	vec3_mult(t, (t_vec3){ctw[2][0], ctw[2][1], ctw[2][2]},
			dim->y / (2 * tan(fov * DEG_RAD)));
	vec3_sub(g, g, t);
}

static t_sphere	*intersect_sphere(t_sphere const *sp,
		t_vec3 const ray, double *t)
{
	
}

static void		render_camera(t_camera const *cam, t_conf const *conf)
{
	t_mat44			ctw;
	t_vec3			camera_real;
	t_vec3			ray;
	t_res			pixel;

	lookat(ctw, cam->loc, cam->dir);
	ray_generic(camera_real, &(conf->r), ctw, cam->fov);
	pixel = (t_res){.x = 0, .y = 0};
	while (pixel.x < conf->r.x)
	{
		while (pixel.y < conf->r.y)
		{
			vec3_mult(ray, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, pixel.x);
			vec3_add(ray, (t_vec3){-ctw[1][0] * pixel.y,
					-ctw[1][1] * pixel.y,
					-ctw[1][2] * pixel.y}, ray);
			vec3_add(ray, camera_real, ray);
			vec3_normalize(ray, ray);
			printf("RAY %lf, %lf, %lf\n", ray[0], ray[1], ray[2]);
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
		render_camera(cur);
		cur = cur->next;
	}
}
