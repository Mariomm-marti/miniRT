/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:37:33 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/04 14:12:34 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/error_handle.h"

void	print_error(t_errcode errcod)
{
	char	mask;
	char	current;

	mask = -1;
	while ((mask = mask + 5) < 64)
		if ((current = errcod << mask >> 59))
			ft_putchar_fd(current == 27 ? ' ' : (current | 96), 1);
	ft_putchar_fd('\n', 1);
}
