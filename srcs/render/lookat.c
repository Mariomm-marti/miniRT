/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:19:51 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/03 18:57:51 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <libft.h>

// TODO Lookat protection along square protection
void	lookat(t_mat44 out, t_vec3 const from, t_vec3 const dir)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;
	t_byte	i;

	vec3_normalize(z, dir);
	vec3_cross(x, (t_vec3){0.0f, 1.0f, 0.0f}, z);
	vec3_cross(y, x, z);
	i = -1;
	while (++i < 4)
	{
		out[0][i] = x[i];
		out[1][i] = y[i];
		out[2][i] = z[i];
		out[3][i] = from[i];
	}
}
