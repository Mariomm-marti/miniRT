/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:19:51 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/21 20:05:24 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <libftmath.h>
#include <libft.h>

void	lookat(t_vec3 const from, t_vec3 const to)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	vec3_sub(z, from, to);
	vec3_normalize(z, z);
	if (z[1]
}
