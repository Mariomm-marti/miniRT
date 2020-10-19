/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:17:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/19 02:09:34 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float		read_val(char **str, float min, float max, t_byte is_int)
{
	float	ret;
	float	pow;
	char	sign;

	sign = **str == '-' && *++*str ? -1 : 1;
	if (!ft_isdigit(**str))
		return (!(g_errno = CONF_INV_NUM));
	ret = **str - '0';
	while (ft_isdigit(*(*str + 1)))
		ret = ret * 10 + (*++*str - '0');
	if (*++*str == '.' && is_int)
		return (!(g_errno = CONF_INV_NUM));
	if (**str != '.')
	{
		if (((ret = ret * sign) < min || ret > max) && min != max)
			g_errno = CONF_INV_NUM;
		return (ret);
	}
	if ((pow = 10) && !ft_isdigit(*++*str))
		return (!(g_errno = CONF_INV_NUM));
	ret = ret * 10 + (**str - '0');
	while (ft_isdigit(*(*str + 1)) && (pow *= 10))
		ret = ret * 10 + (*++*str - '0');
	if (++*str && ((ret = ret / pow * sign) < min || ret > max) && min != max)
		g_errno = CONF_INV_NUM;
	return (ret);
}

t_vec		read_vec(char **str, float min, float max, t_byte is_int)
{
	t_vec	out;

	out.x = read_val(str, min, max, is_int);
	if (*(*str)++ != ',')
		g_errno = CONF_INV_FMT;
	out.y = read_val(str, min, max, is_int);
	if (*(*str)++ != ',')
		g_errno = CONF_INV_FMT;
	out.z = read_val(str, min, max, is_int);
	if (**str)
		g_errno = CONF_INV_FMT;
	return (out);
}

t_color		read_color(char **str)
{
	t_vec 	out;

	out = read_vec(str, 0.0f, 255.0f, 1);
	if (g_errno)
	{
		g_errno = CONF_INV_RGB;
		return (0);
	}
	return ((int)out.x << 16 | (int)out.y << 8 | (int)out.z);
}
