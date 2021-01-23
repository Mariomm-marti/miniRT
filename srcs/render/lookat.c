/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:19:51 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/23 21:35:55 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <libft.h>

void	lookat(t_mat44 out, t_vec3 const from, t_vec3 const dir)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	vec3_normalize(z, dir);
	vec3_cross(x, (t_vec3){0.0f, 1.0f, 0.0f}, z);
	vec3_cross(y, x, z);
	mat44_init_identity(out);
	out[0][0] = x[0];
	out[0][1] = x[1];
	out[0][2] = x[2];
	out[1][0] = y[0];
	out[1][1] = y[1];
	out[1][2] = y[2];
	out[2][0] = z[0];
	out[2][1] = z[1];
	out[2][2] = z[2];
	out[3][0] = from[0];
	out[3][1] = from[1];
	out[3][2] = from[2];
}
