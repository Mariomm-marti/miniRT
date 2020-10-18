/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 01:17:01 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/18 22:56:57 by mmartin-         ###   ########.fr       */
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
	if (((ret = ret / pow * sign) < min || ret > max) && min != max)
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

int			main(int argc, char **argv)
{
	char	*str;
	t_vec	out;

	str = strdup(argv[1]);
	printf("IN: %s\n\n", str);
	out = read_vec(&str, atof(argv[2]), atof(argv[3]), atoi(argv[4]));
	printf("OUT X: %f\nOUT Y: %f\nOUT Z: %f\nERRNO: %llu\n", out.x, out.y, out.z, g_errno);
}
