/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:03:31 by mmartin-          #+#    #+#             */
/*   Updated: 2020/12/31 16:45:50 by mmartin-         ###   ########.fr       */
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
# include <libftmath.h>

typedef unsigned long long int	t_errcode;
typedef unsigned int			t_color;

enum							e_keycodes
{
	KEY_ESC = 53
};

enum							e_errcodes
{
	CONF_MISSING = 0x1BDC6DB5339A5C7ULL,
	CONF_MISSING_PARAM = 0x25D6D8DEE36D2EULL,
	CONF_DUPPED_PARAM = 0x1BDC6D92B0DD82CULL,
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
	CONF_INV_TRIANGLE = 0xDEE36C4126E92ULL,
	EXEC_INV_ARG = 0x4AAED8824D8647ULL,
	EXEC_INV_FNAME = 0x955DB1049B705A5ULL,
	EXEC_INTERNAL_MLX = 0xD66365949F2ULL
};

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
	t_vec3				loc;
	t_vec3				dir;
	t_byte				fov;
	struct s_camera		*next;
}					t_camera;

typedef struct		s_light
{
	t_vec3				loc;
	float				ratio;
	t_color				color;
	struct s_light		*next;
}					t_light;

typedef struct		s_sphere
{
	t_vec3				loc;
	float				diameter;
	t_color				color;
	struct s_sphere		*next;
}					t_sphere;

typedef struct		s_plane
{
	t_vec3				loc;
	t_vec3				dir;
	t_color				color;
	struct s_plane		*next;
}					t_plane;

typedef struct		s_square
{
	t_vec3				loc;
	t_vec3				dir;
	float				side_size;
	t_color				color;
	struct s_square		*next;
}					t_square;

typedef struct		s_cylinder
{
	t_vec3				loc;
	t_vec3				dir;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vec3				a;
	t_vec3				b;
	t_vec3				c;
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

int					read_config(t_conf *conf, char *path, void *mlx_ptr);
void				terminate_program(t_conf *conf, void *mlx_ptr);

#endif
