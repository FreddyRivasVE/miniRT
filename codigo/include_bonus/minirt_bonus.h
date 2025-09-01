/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:14:15 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 20:23:19 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>

# include "../libs/libft/libft.h"
# include "../include_bonus/mrt_struct_bonus.h"

// ========================================================================
// CONSTANTS AND DEFINITIONS
// ========================================================================

# define WIDTH			1280
# define ASPECT_RATIO	1.7777777778
# define PI				3.14159265358979323846
# define EPSILON		1e-6f
# define E_LIGHT		1e-2f
# define E_NORMAL		1e-4f
# define FOCAL_LENGTH	1.0f
# define CHECKERBOARD_SCALE	1.0f

// ========================================================================
// MATERIAL SYSTEM
// ========================================================================

# define MATERIAL_MATTE		1
# define MATERIAL_PLASTIC	2
# define MATERIAL_WOOD		3
# define MATERIAL_SHINY		4

// Default material if not specified
# ifndef MATERIAL_TYPE
#  define MATERIAL_TYPE MATERIAL_PLASTIC
# endif

// Material properties based on type
# if MATERIAL_TYPE == MATERIAL_MATTE
#  define SHININESS_ACTIVE	5.0f
#  define REFLECTION_INTENSITY	0.1f
# elif MATERIAL_TYPE == MATERIAL_PLASTIC
#  define SHININESS_ACTIVE	32.0f
#  define REFLECTION_INTENSITY	0.8f
# elif MATERIAL_TYPE == MATERIAL_WOOD
#  define SHININESS_ACTIVE	8.0f
#  define REFLECTION_INTENSITY	0.3f
# elif MATERIAL_TYPE == MATERIAL_SHINY
#  define SHININESS_ACTIVE	256.0f
#  define REFLECTION_INTENSITY	1.5f
# endif

// ========================================================================
// ANTIALIASING SYSTEM
// ========================================================================

// Default antialiasing setting
# ifndef ANTIALIASING
#  define ANTIALIASING 0
# endif

// MSAA 4x configuration
# if ANTIALIASING == 1
#  define MSAA_SAMPLES 4
# endif

// ========================================================================
// PARSING FUNCTIONS
// ========================================================================

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
int				mrt_check_cn(char *cone);
void			mrt_skip_spaces(char **str);

// ========================================================================
// WINDOW AND UI FUNCTIONS
// ========================================================================

t_window		mrt_setup_window(void);
void			mrt_keyfuncion(mlx_key_data_t keydata, void *data);

// ========================================================================
// INITIALIZATION FUNCTIONS AND MEMORY MANAGEMENT
// ========================================================================

t_vec4			mrt_extract_color(const char *str);
t_vec4			mrt_extrac_vector(const char *str, float w);
int				mrt_init_scene(t_data *data, t_list **file);
void			mrt_clear_scene(t_data *element);

// ========================================================================
// VECTOR OPERATIONS
// ========================================================================

t_vec4			vec4_normalize(t_vec4 v);
t_vec4			vec4_add(t_vec4 a, t_vec4 b);
t_vec4			vec4_scale(t_vec4 v, float s);
t_vec4			vec4_sub(t_vec4 a, t_vec4 b);
t_vec4			vec4_reflect(t_vec4 v, t_vec4 n);
t_vec4			vec4_create(float x, float y, float z, float w);
t_vec4			vec4_cross(t_vec4 a, t_vec4 b);
t_vec4			vec4_mul(t_vec4 a, t_vec4 b);
t_vec4			vec4_clamp(t_vec4 v, float min, float max);
float			vec4_dot(t_vec4 a, t_vec4 b);
float			vect4_length(t_vec4 v);

// ========================================================================
// SCENE ELEMENT SETUP
// ========================================================================

t_camera		*mrt_setup_camera(char **r_cam);
t_ambient		*mrt_setup_ambient(char **r_amb);
t_light			*mrt_setup_light(char **r_light);
t_sphere		*mrt_setup_sphere(char **r_sphere, t_vec4 *rgb);
t_plane			*mrt_setup_plane(char **r_plane, t_vec4 *rgb);
t_cylinder		*mrt_setup_cylinder(char **r_cylinder, t_vec4 *rgb);
t_cone			*mrt_setup_cone(char **r_cone, t_vec4 *rgb);
int				mrt_push_light(t_light **light, t_light *new_node);

// ========================================================================
// RENDERING FUNCTIONS
// ========================================================================

t_camera_view	mrt_compute_camera_view(t_camera *cam, t_window win);
t_ray			mrt_create_ray(t_vec4 origen, t_vec4 direction);
t_vec4			mrt_ray_color(t_ray *ray, t_data *elements);
void			mrt_draw_to_window(t_window window, t_data *elements);

// ========================================================================
// LIGHTING FUNCTIONS
// ========================================================================

t_vec4			mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray);
void			mrt_set_ambient(t_data *el, t_hit *hit, t_vec4 *accum);
void			mrt_setup_lighting_vectors(t_light *l, t_hit *hit,
					t_vec4 *light_dir, float *light_dist);
bool			mrt_intersect_scene(t_data *elements, t_ray *ray,
					t_hit *shadow_hit);
bool			mrt_object_hit_light(t_scene_node *current, float *t,
					t_hit *shadow_hit, t_ray *ray);

// ========================================================================
// GEOMETRIC INTERSECTION FUNCTIONS
// ========================================================================

bool			mrt_hit_sphere(t_ray *ray, t_sphere sphere, t_hit **hit);
bool			mrt_hit_plane(t_ray *ray, t_plane plane, t_hit **hit);
bool			mrt_hit_cylinder(t_ray *ray, t_cylinder cyl, t_hit **hit);
bool			mrt_hit_cylinder_cap(t_ray *ray, t_cylinder cylinder,
					t_cylinder_hits *hits, bool top);
bool			mrt_hit_cylinder_body(t_ray *ray, t_cylinder cylinder,
					float *t_body, t_vec4 *normal_body);
void			mrt_check_object_hit(t_scene_node *node, t_hit_context *ctx);

// ========================================================================
// CONE INTERSECTION FUNCTIONS
// ========================================================================

bool			mrt_hit_cone(t_ray *ray, t_cone cone, t_hit **hit);
t_vec4			mrt_cone_normal_at_point(t_cone cone, t_vec4 point);
float			mrt_calc_cone_slope_factors(t_cone cone, float *sin_alpha);
void			mrt_calc_cone_coefficients(t_ray *ray, t_cone cone, float *abc);
bool			mrt_hit_infinite_cone(t_ray *ray, t_cone cone, float *t_out);
bool			mrt_intersect_base_plane(t_ray *ray, t_cone cone, float *t);
bool			mrt_point_in_base_circle(t_ray *ray, t_cone cone, float t);
bool			mrt_hit_cone_base(t_ray *ray, t_cone cone, float *t_out);
t_cone			mrt_create_adjusted_cone(t_cone cone);

// ========================================================================
// UTILITY FUNCTIONS
// ========================================================================

bool			mrt_get_valid_t(float a, float b, float sqrt_disc,
					float *t_out);

// ========================================================================
// PATTERN FUNCTIONS
// ========================================================================

t_vec4			mrt_apply_checkerboard_pattern(t_data *data, t_vec4 base_color,
					t_hit *hit, t_scene_node *current);
#endif