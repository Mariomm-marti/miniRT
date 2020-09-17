/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:37:33 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/17 19:10:28 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/error_handle.h"

/*
**	DESCRIPTION
**		Converts every t_errcode to text and prints it
**	ERROR SYSTEM DESCRIPTION
**		There are 32 bit in  
*/

void	print_error(t_errcode errcod)
{
	char	mask;
	char	current;

	mask = -1;
	ft_putstr_fd("Error:\n", 1);
	while ((mask = mask + 5) < 64)
		if ((current = errcod << mask >> 59))
			ft_putchar_fd(current == 27 ? ' ' : (current | 96), 1);
	ft_putchar_fd('\n', 1);
}
