/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 19:51:06 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/04 20:02:46 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	print_error(unsigned long long int errcod)
{
	char	mask;
	char	current;

	mask = -1;
	while ((mask = mask + 5) < 64)
		if ((current = errcod << mask >> 59))
			ft_putchar_fd(current == 27 ? ' ' : (current | 96), 1);
}

unsigned long long int	parse_errcode(char *str)
{
	unsigned long long int	final;

	final = 0;
	while (*str)
	{
		final = (final << 5ULL) | (*str == ' ' ? 27ULL : *str & 31ULL);
		str++;
	}
	return (final);
}

int		main(int argc, char **argv)
{
	char	out[64];

	if (argc != 2)
		return (1);
	if ((*argv[1] >= 'a' && *argv[1] <= 'z') || *argv[1] == ' ')
		printf("0x%llXULL", parse_errcode(*(argv + 1)));
	else
		print_error(strtoull(argv[1], NULL, 16));
}
