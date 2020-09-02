/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:45:05 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/02 20:42:40 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "../includes/error_handle.h"

int		main(int argc, char **argv)
{
	if (argc > 1 || !**argv)
		return (1);
	print_error(CONF_MISSING);
}
