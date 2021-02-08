/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:24:41 by mmartin-          #+#    #+#             */
/*   Updated: 2021/02/08 19:44:48 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned int	t_color;

static t_color  add_color(t_color const a, t_color const b, double ratio)
{
    t_color     result;
    t_color     ar;
    t_color     br;

    ar = a >> 16 & 255;
    br = (int)((b >> 16 & 255) * ratio);
    result = (ar + br > 255 ? 255 : ar + br) << 16;
    ar = a >> 8 & 255;
    br = (int)((b >> 8 & 255) * ratio);
    result |= (ar + br > 255 ? 255 : ar + br) << 8;
    ar = a & 255;
    br = (int)((b & 255) * ratio);
    result |= (ar + br > 255 ? 255 : ar + br);
    return (result);
}

static t_color	mult_color(t_color const a, t_color const b, double ratio)
{
	return ((int)((a >> 16 & 255) * (b >> 16 & 255) * ratio / 255) << 16 |
			(int)((a >> 8 & 255) * (b >> 8 & 255) * ratio / 255) << 8 |
			(int)((a & 255) * (b & 255) * ratio / 255));
}

int		main(void)
{
	t_color a = 0x0000ff;
	t_color b = 0xffffff;

	printf("%.6X\n", add_color(a, b, 0.5));
	printf("%.6X\n", mult_color(a, b, 0.5f));
}
