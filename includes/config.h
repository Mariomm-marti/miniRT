/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:56:24 by mmartin-          #+#    #+#             */
/*   Updated: 2021/01/29 10:30:34 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "minirt.h"

/*
**	Basic getters for configuration values, exhaustive description
**	is present in function body
*/

float				read_val(char *str, t_byte is_int);
void				read_vec(t_vec3 out, char *str, float min, float max);
t_color				read_color(char *str);

/*
**	Creators for each type of element, note that cameras accept an additional
**	parameter for mlx image creation (man /usr/share/man/man1_/mlx_new_image.1
**	at campus iMac).
**	Those functions are pretty much descriptive so no comments were added
*/

t_camera			*create_camera(t_conf *conf, char *str);
t_light				*create_light(t_conf *conf, char *str);
t_sphere			*create_sphere(t_conf *conf, char *str);
t_plane				*create_plane(t_conf *conf, char *str);
t_square			*create_square(t_conf *conf, char *str);
t_cylinder			*create_cylinder(t_conf *conf, char *str);
t_triangle			*create_triangle(t_conf *conf, char *str);

/*
**	Allows fetching element at index, returns NULL if element is out of bounds
*/

t_camera			*get_camera(t_conf *conf, size_t index);
t_light				*get_light(t_conf *conf, size_t index);
t_sphere			*get_sphere(t_conf *conf, size_t index);
t_plane				*get_plane(t_conf *conf, size_t index);
t_square			*get_square(t_conf *conf, size_t index);
t_cylinder			*get_cylinder(t_conf *conf, size_t index);
t_triangle			*get_triangle(t_conf *conf, size_t index);

/*
**	Functions for releasing heap for each element created, note that cameras
**	require an additional parameter for mlx image destruction
**	(man /usr/share/man/man1_/mlx_new_image.1 at campus iMac).
*/

void				free_cameras(t_conf *conf, void *mlx_ptr);
void				free_lights(t_conf *conf);
void				free_spheres(t_conf *conf);
void				free_planes(t_conf *conf);
void				free_squares(t_conf *conf);
void				free_cylinders(t_conf *conf);
void				free_triangles(t_conf *conf);

#endif
