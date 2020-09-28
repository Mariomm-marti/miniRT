/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:45:05 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/26 13:35:19 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h> // delet
#include <string.h> // delet
#include "../includes/minirt.h"

int			main(int argc, char **argv)
{
	t_errcode	errcode;
	float		min;
	float		max;
	float		out;
	char		*str;

	str = strdup(argv[1]);
	if ((errcode = read_rnum(&out, &str, 0.0f, 0.0f)))
	{
		print_error(errcode);
		return (1);
	}
	printf("%f <-> %d\n", out, *str);
}
