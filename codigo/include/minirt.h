/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:14:15 by brivera           #+#    #+#             */
/*   Updated: 2025/08/10 10:51:48 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>

//libs42
# include "../libs/libft/libft.h"
# include "../include/mrt_struct.h"

# define WIDTH 800
# define ASPECT_RATIO 1.7777777778
# define PI 3.14159265358979323846

//parce
t_list			*mrt_read_file(char *file);
int				mrt_check_ambient(char *r_data);
int				mrt_check_rgb(char **ptr);
int				mrt_check_camera(char *camera);
int				mrt_parse_float(char **str, double *out);
void			mrt_skip_spaces(char **str);
int				mrt_parse_vector(char **str, double min, double max);
int				mrt_is_view_in_range(double val, double min, double max);
int				mrt_check_light(char *light);
int				mrt_check_sp(char *sphere);
int				mrt_read_row_data(t_list *lst);
int				mrt_check_pl(char *plane);
//window
t_window		mrt_setup_window(void);
void			mrt_keyfuncion(mlx_key_data_t keydata, void *data);
//init_element
int				mrt_init_scene(t_data *data, t_list **file);
//operaciones de vectores
t_vec4			vec4_normalize(t_vec4 v);
t_vec4			vec4_add(t_vec4 a, t_vec4 b);
t_vec4			vec4_scale(t_vec4 v, float s);
float			vec4_dot(t_vec4 a, t_vec4 b);
t_vec4			vec4_sub(t_vec4 a, t_vec4 b);
t_vec4			vec4_reflect(t_vec4 v, t_vec4 n);
t_vec4			vec4_create(float x, float y, float z, float w);
t_vec4			vec4_cross(t_vec4 a, t_vec4 b);
t_vec4			vec4_mul(t_vec4 a, t_vec4 b);
t_vec4			vec4_clamp(t_vec4 v, float min, float max);
//liberacion de memoria
void			mrt_clear_scene(t_data *element);
//elements
t_camera		*setup_test_camera(void);
t_point_light	*setup_test_light(void);
t_ambient		*setup_test_ambient(void);
t_sphere		*setup_test_sphere(t_vec4 center, float radius);
t_plane			*setup_test_plane(void);
//render
bool			mrt_hit_sphere(t_ray ray, t_sphere sphere, float *t_hit);
t_camera_view	mrt_compute_camera_view(t_camera *cam);
void			mrt_draw_to_window(t_window window, t_data *elements);

#endif