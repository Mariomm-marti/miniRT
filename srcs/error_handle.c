/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:37:33 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/24 17:30:59 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "../includes/minirt.h"

/*
**	DESCRIPTION
**		Converts every t_errcode to text and prints it
**	ERROR SYSTEM DESCRIPTION
**		t_errcode is 64-bit type. I skip the 4 most significant bytes, then
**		the remaining 60 bits are split in groups of 5 bits, which allows to
**		use the basic a-z and a reserved character ' '. It can be displayed
**		as following (in the following example it's 32-bit instead of 64-bit):
**
**		+ - + - - - + - - - + - - - + - - - + - - - + - - - +
**		|00 | 00000 | 00000 | 00000 | 00000 | 00000 | 00000 |
**		+ - + - - - + - - - + - - - + - - - + - - - + - - - +
**		R	0 char	1 char	2 char	3 char	4 char	5 char	...
**
**		Note that R is a reserved space for future control flows if needed
**		This system replaces 8-bit chars with 5-bit chars as most
**		ASCII characters are not necessary for error flow management.
**
**		You can store up to 12 characters string in data segment as integer
**	RETURN VALUES
**		None
*/

void	print_error(t_errcode errcod)
{
	char	mask;
	char	current;

	mask = -1;
	if (!errcod)
		return ;
	ft_putstr_fd("Error:\n", 1);
	while ((mask = mask + 5) < 64)
		if ((current = errcod << mask >> 59))
			ft_putchar_fd(current == 27 ? ' ' : (current | 96), 1);
	ft_putchar_fd('\n', 1);
}
