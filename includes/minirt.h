/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:03:31 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/01 19:51:34 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

typedef struct		s_vec
{
	float				x;
	float				y;
	float				z;
}					t_vec;

typedef struct		s_ambient
{
	float				ratio;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
}					t_ambient;

typedef struct		s_camera
{
	struct s_vec		coods;
	struct s_vec		facing;
	t_byte				fov;
	struct s_camera		*next;
}					t_camera;

typedef struct		s_light
{
	struct s_vec		coords;
	float				ratio;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_light		*next;
}					t_light;

typedef struct		s_sphere
{
	struct s_vec		coords;
	float				diameter;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_sphere		*next;
}					t_sphere;

typedef struct		s_plane
{
	struct s_vec		coords;
	struct s_vec		facing;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_plane		*next;
}					t_plane;

typedef struct		s_square
{
	struct s_vec		coords;
	struct s_vec		facing;
	float				side_size;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_square		*next;
}					t_square;

typedef struct		s_cylinder
{
	struct s_vec		coords;
	struct s_vec		facing;
	float				diameter;
	float				height;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct		s_triangle
{
	struct s_vec		side_a;
	struct s_vec		side_b;
	struct s_vec		side_c;
	t_byte				red;
	t_byte				green;
	t_byte				blue;
	struct s_triangle	*next;
}					t_triangle;

typedef struct		s_conf
{
	unsigned short		width;
	unsigned short		height;
	struct s_ambient	*ambient;
	struct s_camera		*cameras;
	struct s_light		*lights;
	struct s_sphere		*spheres;
	struct s_plane		*planes;
	struct s_square		*squares;
	struct s_cylinder	*cylinders;
	struct s_triangle	*triangles;
}					t_conf;

#endif
