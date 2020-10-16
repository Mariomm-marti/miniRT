/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:17:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/16 22:56:50 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float		read_val(char **str, float min, float max, t_byte is_int)
{
	float	ret;
	float	dec_pow;
	char	sign;

	sign = **str == '-' && *++str ? -1 : 1;
	if (!ft_isdigit(**str))
		return (!(g_errno = CONF_INV_NUM));
	ret = **str - '0';
	while (ft_isdigit(*(*str + 1)))
		ret = ret * 10 + (*++*str - '0');
	if (is_int && *++*str == '.')
		return (!(g_errno = CONF_INV_NUM));
	if (**str != '.'	)
	{
		ret = ret * sign;
		if (min != max && (ret < min || ret > max))
			g_errno = CONF_INV_NUM;
		return (ret);
	}
	ret = *
	return (ret / dec_pow * sign);
}

t_vec		read_vec(char **str, float min, float max, t_byte is_int)
{
	t_vec	out;

	out.x = read_val(str, min, max, is_int);
	out.y = read_val(str, min, max, is_int);
	out.z = read_val(str, min, max, is_int);
	return (out);
}

t_color		read_color(char **str)
{
	t_vec	vec;
	t_color	color;

	vec = read_vec(str, 0.0f, 255.0f, 1);
	color = (int)vec.x;
	color = (color << 8) | (int)vec.y;
	color = (color << 8) | (int)vec.z;
	if (g_errno)
		g_errno = CONF_INV_RGB;
	return (color);
}

int			main(int argc, char **argv)
{
	char *str;

	str = strdup(argv[1]);
	printf("IN: %s\n\n", str);
	printf("OUT: %f\nERRNO: %llu\n", read_val(&str, 0.0f, 0.0f, 0), g_errno);
}
