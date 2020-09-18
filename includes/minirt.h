/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:03:31 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/18 20:28:40 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#ifndef SCREEN_WIDTH
# define SCREEN_WIDTH 1920
#endif

#ifndef SCREEN_HEIGHT
# define SCREEN_HEIGHT 1080
#endif

# include <libft.h>

typedef unsigned long long int	t_errcode;

typedef enum		e_errcodes
{
	CONF_MISSING = 0x1BDC6DB5339A5C7ULL,
	CONF_INV_FMT = 0x1BDC6D8824D99B4ULL,
	CONF_INV_RES = 0x6F71B6209372ULL,
	CONF_INV_AMB = 0x6F71B6209361ULL,
	CONF_INV_CAM = 0x6F71B6209363ULL,
	CONF_INV_LIGHT = 0x6F71B620936CULL,
	CONF_INV_SPHERE = 0xDEE36C4126E70ULL,
	CONF_INV_PLANE = 0xDEE36C4126E0CULL,
	CONF_INV_SQUARE = 0xDEE36C4126E71ULL,
	CONF_INV_CYLINDER = 0xDEE36C4126C79ULL,
	CONF_INV_TRIANGLE = 0xDEE36C4126E92ULL
}					t_errcodes;

typedef struct		s_vec
{
	float				x;
	float				y;
	float				z;
}					t_vec;

typedef struct		s_res
{
	unsigned short		x;
	unsigned short		y;
}					t_res;

typedef struct		s_amb
{
	float				ratio;
	unsigned int		color;
}					t_amb;

typedef struct		s_camera
{
	struct s_vec		coods;
	struct s_vec		facing;
	t_byte				fov;
}					t_camera;

typedef struct		s_light
{
	struct s_vec		coords;
	float				ratio;
	unsigned int		color;
}					t_light;

typedef struct		s_sphere
{
	struct s_vec		coords;
	float				diameter;
	unsigned int		color;
}					t_sphere;

typedef struct		s_plane
{
	struct s_vec		coords;
	struct s_vec		facing;
	unsigned int		color;
}					t_plane;

typedef struct		s_square
{
	struct s_vec		coords;
	struct s_vec		facing;
	float				side_size;
	unsigned int		color;
}					t_square;

typedef struct		s_cylinder
{
	struct s_vec		coords;
	struct s_vec		facing;
	float				diameter;
	float				height;
	unsigned int		color;
}					t_cylinder;

typedef struct		s_triangle
{
	struct s_vec		side_a;
	struct s_vec		side_b;
	struct s_vec		side_c;
	unsigned int		color;
}					t_triangle;

typedef struct		s_conf
{
	struct s_res		res;
	struct s_amb		amb;
	struct s_list		*cameras;
	struct s_list		*lights;
	struct s_list		*spheres;
	struct s_list		*planes;
	struct s_list		*squares;
	struct s_list		*cylinders;
	struct s_list		*triangles;
}					t_conf;

void				print_error(t_errcode errcod);

t_errcode			read_conf(t_conf *conf, char const *path);

#endif
