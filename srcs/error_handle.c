/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:37:33 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/24 18:39:12 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "../includes/minirt.h"
#include "../includes/config.h"

/*
**	DESCRIPTION
**		Converts every t_errcode to text and prints it
**	ERROR SYSTEM DESCRIPTION
**		t_errcode is 64-bit type. I skip the 4 most significant bits, then
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

void	print_error(void)
{
	char	mask;
	char	current;

	mask = -1;
	if (!g_errno)
		return ;
	ft_putstr_fd("Error:\n", 1);
	while ((mask = mask + 5) < 64)
		if ((current = g_errno << mask >> 59))
			ft_putchar_fd(current == 27 ? ' ' : (current | 96), 1);
	ft_putchar_fd('\n', 1);
}

/*
**	DESCRIPTION
**		Takes configuration and a pointer to mlx, and free
**		all elements in configuration
**	RETURN VALUES
**		None
*/

void	terminate_program(t_conf *conf, void *mlx_ptr)
{
	if (!conf || !mlx_ptr)
		exit(!!g_errno);
	free_cameras(conf, mlx_ptr);
	free_lights(conf);
	free_spheres(conf);
	free_planes(conf);
	free_squares(conf);
	free_cylinders(conf);
	free_triangles(conf);
	// TODO remove it
	system("leaks miniRT");
	exit(!!(g_errno));
}
