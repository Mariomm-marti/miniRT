/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cameras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:32:02 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/23 21:43:16 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>
#include <libftmath.h>
#include <math.h>

static void		ray_generic(t_vec3 g, t_mat44 const ctw, t_byte const fov)
{
	t_vec3	t;

	vec3_mult(g, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, -SCREEN_WIDTH / 2);
	vec3_mult(t, (t_vec3){ctw[1][0], ctw[0][1], ctw[0][2]}, SCREEN_HEIGHT / 2);
	vec3_add(g, t, g);
	vec3_mult(t, (t_vec3){ctw[2][0], ctw[2][1], ctw[2][2]},
			SCREEN_HEIGHT / (2 * tan(fov * DEG_RAD)));
	vec3_sub(g, g, t);
}

static t_inter	intersect_sphere(t_sphere const *sp, 

static void		render_camera(t_camera const *cam)
{
	t_mat44			ctw;
	t_vec3			camera_real;
	t_vec3			ray;
	unsigned short	x;
	unsigned short	y;

	lookat(ctw, cam->loc, cam->dir);
	ray_generic(camera_real, ctw, cam->fov);
	x = 0;
	y = 0;
	while (x < SCREEN_WIDTH)
	{
		while (y < SCREEN_HEIGHT)
		{
			vec3_mult(ray, (t_vec3){ctw[0][0], ctw[0][1], ctw[0][2]}, x);
			vec3_add(ray, (t_vec3){-ctw[1][0] * y,
					-ctw[1][1] * y,
					-ctw[1][2] * y}, ray);
			vec3_add(ray, camera_real, ray);
			vec3_normalize(ray, ray);
			printf("RAY %lf, %lf, %lf\n", ray[0], ray[1], ray[2]);
			y++;
		}
		x++;
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
