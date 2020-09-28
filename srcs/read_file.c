/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:58:11 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/26 14:39:35 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // review
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <get_next_line.h>
#include "../includes/minirt.h"

t_errcode		read_color(t_color *out, char const *line, t_byte len)
{
	t_color		current_color;

	if (len >= 3 || !ft_isdigit(*line) || (current_color = *line - '0') < 0)
		return (CONF_INV_RGB);
	while (ft_isdigit(*(line + 1)))
		current_color = current_color * 10 + (*++line - '0');
	if (current_color > 255)
		return (CONF_INV_RGB);
	*out = (*out << (8 * !!len)) | current_color;
	if (*++line == ',')
		return (read_color(out, line + 1, len + 1));
	if (len != 2)
		return (CONF_INV_RGB);
	return (*line ? CONF_INV_FMT : 0);
}

t_errcode		read_rnum(float *out, char **line, float min, float max)
{
	char					sign;
	unsigned long long int	dec_pow;
	t_byte					is_zero;

	sign = (**line == '-' && ++*line) ? -1 : 1;
	if (!ft_isdigit(**line))
		return (CONF_INV_FMT);
	*out = **line - '0';
	while (ft_isdigit(*(*line + 1)))
		*out = *out * 10 + (*++*line - '0');
	if (*++*line != '.')
		return (0);
	if (!ft_isdigit(*++*line))
		return (CONF_INV_NUM);
	is_zero = *out == 0.0f;
	dec_pow = 10;
	*out = (float)is_zero + (*out * 10 + (**line - '0'));
	while (ft_isdigit(*(*line + 1)) && (dec_pow *= 10))
		*out = *out * 10 + (*++*line - '0');
	*out = (*out / dec_pow - (float)is_zero) * sign;
	if (++*line && min == max)
		return (0);
	return (*out < min || *out > max ? CONF_INV_NUM : 0);
}

t_errcode		read_vec(t_vec *out, char **line, float min, float max)
{
	t_errcode	error;

	if ((error = read_rnum(out->x, line, min, max)))
		return (error);
	if (out
}
