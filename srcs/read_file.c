/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 19:41:25 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/04 20:43:55 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error_handle.h"

float	readv(char *ln)
{
	static int	lp = 0;
	float		final;
	int			decimal;

	if ((!ft_isdigit(*(ln + lp - 1)) || !ft_isdigit(*(ln + lp + 1))) &&
			(*(ln + lp) == ',' || *(ln + lp) == '.'))
	{
		// TODO error handle
		return (0.0f);
	}
	return (final);
}
