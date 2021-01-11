/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:18:44 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/07 21:24:29 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <mlx.h>

static int	validate_args(int argc, char **argv)
{
	char	*dptr;

	if (argc != 2 && argc != 3)
		g_errno = EXEC_INV_ARG;
	else if (!(dptr = ft_strrchr(*(argv + 1), '.')) || ft_strcmp(".rt", dptr))
		g_errno = EXEC_INV_FNAME;
	else if (argc == 3 && ft_strcmp("--save", *(argv + 2)))
		g_errno = EXEC_INV_ARG;
	return (!!g_errno);
}

int			main(int argc, char **argv)
{
	t_conf	conf;
	void	*mlxptr;

	ft_bzero(&conf, sizeof(t_conf));
	if (validate_args(argc, argv) || !(mlxptr = mlx_init()))
	{
		print_error();
		return (0);
	}
	read_config(&conf, *(argv + 1), mlxptr);
//	// 
	terminate_program(&conf, mlxptr);
}
