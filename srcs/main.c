/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:45:05 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/21 20:38:59 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "../includes/minirt.h"

int			main(int argc, char **argv)
{
	float out;

	if (argc != 2)
		return (1);
	out = 0;
	read_rnumber(&out, argv[1], 0.0f, 1.0f);
}
