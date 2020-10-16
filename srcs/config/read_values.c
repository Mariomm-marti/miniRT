/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:17:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/16 02:47:40 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float		read_val(char const *str, float min, float max, t_byte is_int)
{
	float	ret;
	float	dec_pow;
	char	sign;

	sign = *str == '-' ? !(*str++) - 1 : 1;
	if (!ft_isdigit(*str))
		return ((float)(!(g_errno = CONF_INV_NUM)));
	ret = *str - '0';
	while (ft_isdigit(*(str + 1)))
		ret = ret * 10 + (*str++ - '0');
	if (is_int && *++str != '.' && ret >= min && ret <= max)
		return (ret);
	if (is_int)
		return ((float)(!(g_errno = CONF_INV_NUM)));
	if (*str != '.')
		return ((float)(!(g_errno = CONF_INV_FMT)));
	ret = ret * 10 + (*++str - '0');
	dec_pow = 10;
	while (ft_isdigit(*(str + 1)) && (dec_pow *= 10))
		ret = ret * 10 + (*str++ - '0');
	if ((ret = ret / dec_pow * sign) < min || ret > max)
		return ((float)(!(g_errno = CONF_INV_NUM)));
	return (ret);
}

t_vec		read_vec(char const *str, float min, float max, t_byte is_int)
{
	t_vec	out;

	out.x = read_val(str, min, max, is_int);
	out.y = read_val(str, min, max, is_int);
	out.z = read_val(str, min, max, is_int);
	return (out);
}

t_color		read_color(char const *str)
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
	printf("OUT: %f\nERRNO: %llu\n", read_val(argv[1], atof(argv[2]), atof(argv[3]), atoi(argv[4])), g_errno);
}
