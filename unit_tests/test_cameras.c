/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 22:50:52 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/25 22:58:31 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdlib.h>
#include <stdio.h>

int		main(int argc, char **argv)
{
	t_camera	*cam;
	t_conf		config;
	void		*mlx_ptr;

	if (!(mlx_ptr = mlx_init()))
		return (1);
	if (!(create_camera(&config, *(argv + 1), mlx_ptr)))
	{
		printf("ERROR CREATING CAMERA\n");
		print_error();
		return (1);
	}
	cam = get_camera(&config, 0);
	if (!cam)
	{
		printf("WTF\n");
		return (1);
	}
	printf("CAM:\n");
	printf("IMG PTR: %p\n", cam->img);
	printf("GRID PTR: %p\n", cam->grid);
}
