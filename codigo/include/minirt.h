/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:14:15 by brivera           #+#    #+#             */
/*   Updated: 2025/08/23 20:33:01 by brivera          ###   ########.fr       */
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
# define EPSILON 1e-6f

//parce
t_list			*mrt_read_file(char *file);
int				mrt_check_ambient(char *r_data);
int				mrt_check_rgb(char **ptr);
int				mrt_check_camera(char *camera);
int				mrt_parse_float(char **str, double *out);
int				mrt_parse_vector(char **str, double min, double max, int flag);
int				mrt_is_view_in_range(double val, double min, double max);
int				mrt_check_light(char *light);
int				mrt_check_sp(char *sphere);
int				mrt_read_row_data(t_list *lst);
int				mrt_check_pl(char *plane);
int				mrt_check_cy(char *cylinder);
void			mrt_skip_spaces(char **str);
//window
t_window		mrt_setup_window(void);
void			mrt_keyfuncion(mlx_key_data_t keydata, void *data);
//init_element
int				mrt_init_scene(t_data *data, t_list **file);
t_vec4			mrt_extract_color(const char *str);
t_vec4			mrt_extrac_vector(const char *str, float w);
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
t_camera		*mrt_setup_camera(char **r_cam);
t_ambient		*mrt_setup_ambient(char **r_amb);
t_light			*mrt_setup_light(char **r_light);
t_sphere		*mrt_setup_sphere(char **r_sphere, t_vec4 *rgb);
t_plane			*mrt_setup_plane(char **r_plane, t_vec4 *rgb);
t_cylinder		*mrt_setup_cylinder(char **r_cylinder, t_vec4 *rgb);
//render
t_camera_view	mrt_compute_camera_view(t_camera *cam, t_window win);
bool			mrt_hit_sphere(t_ray *ray, t_sphere sphere, t_hittable **hit);
void			mrt_draw_to_window(t_window window, t_data *elements);
bool			mrt_hit_plane(t_ray ray, t_plane plane, t_hittable **hit);
bool			mrt_hit_cylinder(t_ray ray, t_cylinder cyl, t_hittable **hit);
t_vec4			mrt_light_color(t_data *elements, t_hittable *hit, t_ray *ray);
#endif