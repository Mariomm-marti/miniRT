/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:03:31 by mmartin-          #+#    #+#             */
/*   Updated: 2020/10/29 22:50:16 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1920
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif

# include <libft.h>

typedef unsigned long long int	t_errcode;
typedef unsigned int			t_color;

enum							e_keycodes
{
	KEY_ESC = 53
};

enum							e_errcodes
{
	CONF_MISSING = 0x1BDC6DB5339A5C7ULL,
	CONF_INV_FMT = 0x1BDC6D8824D99B4ULL,
	CONF_INV_RGB = 0x1BDC6D8824DC8E2ULL,
	CONF_INV_NUM = 0x1BDC6D8824DBAADULL,
	CONF_INV_RES = 0x6F71B6209372ULL,
	CONF_INV_AMB = 0x6F71B6209361ULL,
	CONF_INV_CAM = 0x6F71B6209363ULL,
	CONF_INV_LIGHT = 0x6F71B620936CULL,
	CONF_INV_SPHERE = 0xDEE36C4126E70ULL,
	CONF_INV_PLANE = 0xDEE36C4126E0CULL,
	CONF_INV_SQUARE = 0xDEE36C4126E71ULL,
	CONF_INV_CYLINDER = 0xDEE36C4126C79ULL,
	CONF_INV_TRIANGLE = 0xDEE36C4126E92ULL
};

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
	t_color				color;
}					t_amb;

typedef struct		s_camera
{
	void				*img;
	int					*grid;
	int					bpp;
	int					sline;
	struct s_vec		loc;
	struct s_vec		dir;
	t_byte				fov;
	struct s_camera		*next;
}					t_camera;

typedef struct		s_light
{
	struct s_vec		loc;
	float				ratio;
	t_color				color;
	struct s_light		*next;
}					t_light;

typedef struct		s_sphere
{
	struct s_vec		loc;
	float				diameter;
	t_color				color;
	struct s_sphere		*next;
}					t_sphere;

typedef struct		s_plane
{
	struct s_vec		loc;
	struct s_vec		dir;
	t_color				color;
	struct s_plane		*next;
}					t_plane;

typedef struct		s_square
{
	struct s_vec		loc;
	struct s_vec		dir;
	float				side_size;
	t_color				color;
	struct s_square		*next;
}					t_square;

typedef struct		s_cylinder
{
	struct s_vec		loc;
	struct s_vec		dir;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct		s_triangle
{
	struct s_vec		side_a;
	struct s_vec		side_b;
	struct s_vec		side_c;
	t_color				color;
	struct s_triangle	*next;
}					t_triangle;

typedef struct		s_conf
{
	struct s_res		r;
	struct s_amb		a;
	struct s_camera		*c;
	struct s_light		*l;
	struct s_sphere		*sp;
	struct s_plane		*pl;
	struct s_square		*sq;
	struct s_cylinder	*cy;
	struct s_triangle	*tr;
}					t_conf;

t_errcode			g_errno;

void				print_error();

float				read_val(char *str, t_byte is_int);
t_vec				read_vec(char *str, float min, float max);
t_color				read_color(char *str);

t_camera			*create_camera(t_conf *conf, char *str, void *mlx_ptr);
t_light				*create_light(t_conf *conf, char *str);
t_sphere			*create_sphere(t_conf *conf, char *str);
t_plane				*create_plane(t_conf *conf, char *str);
t_square			*create_square(t_conf *conf, char *str);
t_camera			*get_camera(t_conf *conf, size_t index);
t_light				*get_light(t_conf *conf, size_t index);
t_sphere			*get_sphere(t_conf *conf, size_t index);
t_plane				*get_plane(t_conf *conf, size_t index);
t_square			*get_square(t_conf *conf, size_t index);
void				free_cameras(t_conf *conf, void *mlx_ptr);
void				free_lights(t_conf *conf);
void				free_spheres(t_conf *conf);
void				free_planes(t_conf *conf);
void				free_squares(t_conf *conf);

#endif
