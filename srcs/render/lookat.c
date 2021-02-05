/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:19:51 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/05 12:55:24 by mmartin-         ###   ########.fr       */
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
	t_byte	i;

	vec3_normalize(z, dir);
	if (z[1] != 1.0f && z[1] != -1.0f)
	{
		vec3_cross(x, (t_vec3){0.0f, 1.0f, 0.0f}, z);
		vec3_cross(y, x, z);
	}
	else
	{
		ft_memcpy(x, (t_vec3){0.0f, 0.0f, 1.0f}, sizeof(t_vec3));
		ft_memcpy(y, (t_vec3){1.0f, 0.0f, 0.0f}, sizeof(t_vec3));
		ft_memcpy(z, (t_vec3){0.0f, z[1], 0.0f}, sizeof(t_vec3));
	}
	i = -1;
	while (++i < 4)
	{
		out[0][i] = x[i];
		out[1][i] = y[i];
		out[2][i] = z[i];
		out[3][i] = from[i];
	}
}
