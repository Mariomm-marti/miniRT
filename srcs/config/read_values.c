/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:17:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/12/23 22:51:10 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdlib.h>
#include <libft.h>

static float	read_vec_val(char **str)
{
	float	final;
	float	dec_pow;
	char	sign;

	sign = **str == '-' && ++*str ? -1 : 1;
	if (!ft_isdigit(**str))
		return (!(g_errno = CONF_INV_FMT));
	final = **str - '0';
	while (ft_isdigit(*(*str + 1)))
		final = final * 10 + (*++*str - '0');
	if (*++*str != '.')
		return (final * sign);
	if (!ft_isdigit(*++*str))
		return (!(g_errno = CONF_INV_FMT));
	final = final * 10 + (**str - '0');
	dec_pow = 10;
	while (ft_isdigit(*(*str + 1)))
	{
		final = final * 10 + (*++*str - '0');
		dec_pow = dec_pow * 10;
	}
	++*str;
	return (final / dec_pow * sign);
}

float			read_val(char *str, t_byte is_int)
{
	float	final;
	float	dec_pow;
	char	sign;

	sign = *str == '-' && ++str ? -1 : 1;
	if (!ft_isdigit(*str))
		return (!(g_errno = CONF_INV_NUM));
	final = *str - '0';
	while (ft_isdigit(*(str + 1)))
		final = final * 10 + (*++str - '0');
	if (*++str && is_int)
		return (!(g_errno = CONF_INV_FMT));
	if (is_int)
		return (final * sign);
	if (*str != '.')
		return (*str ? !(g_errno = CONF_INV_FMT) : final * sign);
	if (!ft_isdigit(*++str))
		return (!(g_errno = CONF_INV_FMT));
	dec_pow = 10;
	final = final * 10 + (*str - '0');
	while (ft_isdigit(*(str + 1)) && (dec_pow *= 10))
		final = final * 10 + (*++str - '0');
	if (*++str)
		return (!(g_errno = CONF_INV_FMT));
	return (final / dec_pow * sign);
}

void			read_vec(t_vec3 out, char *str, float min, float max)
{
	char		*dup;

	dup = ft_strdup(str);
	str = dup;
	out[0] = read_vec_val(&dup);
	if (*dup++ != ',')
		g_errno = CONF_INV_FMT;
	out[1] = read_vec_val(&dup);
	if (*dup++ != ',')
		g_errno = CONF_INV_FMT;
	out[2] = read_vec_val(&dup);
	if (*dup++)
		g_errno = CONF_INV_FMT;
	if (min != max && (out[0] < min || out[0] > max || out[1] < min ||
				out[1] > max || out[2] < min || out[2] > max))
		g_errno = CONF_INV_NUM;
	free(str);
}

t_color			read_color(char *str)
{
	t_color	red;
	t_color	green;
	t_color	blue;

	if (!ft_isdigit(*str))
		g_errno = CONF_INV_RGB;
	red = *str - '0';
	while (ft_isdigit(*(str + 1)))
		red = red * 10 + (*++str - '0');
	if (*++str != ',' || red > 255 || !ft_isdigit(*++str))
		g_errno = CONF_INV_RGB;
	green = *str - '0';
	while (ft_isdigit(*(str + 1)))
		green = green * 10 + (*++str - '0');
	if (*++str != ',' || green > 255 || !ft_isdigit(*++str))
		g_errno = CONF_INV_RGB;
	blue = *str - '0';
	while (ft_isdigit(*(str + 1)))
		blue = blue * 10 + (*++str - '0');
	if (*++str || blue > 255)
		g_errno = CONF_INV_RGB;
	return (red << 16 | green << 8 | blue);
}
