/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:30:02 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 13:37:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>

/* --- Basic Types --- */
typedef double	t_real;
typedef int		t_status;
typedef int		t_bool;

/* --- Maths --- */
typedef struct s_vec3
{
	t_real	x;
	t_real	y;
	t_real	z;
}	t_vec3;

typedef t_vec3	t_point3;

typedef struct s_mat4
{
	t_real	m[4][4];
}	t_mat4;

typedef struct s_poly
{
	t_real	a;
	t_real	half_b;
	t_real	c;
	t_real	min;
	t_real	max;
	t_real	root1;
	t_real	root2;
}	t_poly;

typedef struct s_color
{
	t_real	r;
	t_real	g;
	t_real	b;
}	t_color;

/* --- Raytracing --- */
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
	t_real		min;
	t_real		max;
}	t_ray;

/* --- Objects --- */
typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_object_type;

typedef struct s_sphere
{
	t_point3	center;
	t_real		radius;
	t_real		radius_squared;
}	t_sphere;

typedef struct s_plane
{
	t_point3	origin;
	t_vec3		normal;
	t_real		d;
}	t_plane;

typedef enum e_cylinder_cap
{
	CAP_TOP,
	CAP_BOTTOM,
	CAP_NONE
}	t_cylinder_cap;
typedef struct s_cylinder_vars
{
	t_poly	eq_vars;
	t_vec3	oc;
	t_real	dot_dir_axis;
	t_real	dot_oc_axis;
	t_real	half_height;
	t_real	projection;
	t_vec3	top_center;
	t_vec3	bottom_center;
	t_real	cap_denom;
}	t_cylinder_vars;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	t_real		radius;
	t_real		radius_squared;
	t_real		height;
}	t_cylinder;

typedef struct s_object
{
	t_object_type	type;
	t_color			color;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} u_data;
	struct s_object	*next;
}	t_object;

typedef struct s_hit_record
{
	t_object	*object;
	t_point3	hit_point;
	t_vec3		normal;
	t_real		t;
	t_bool		front_face;
	t_color		color;
}	t_hit_record;

/* --- Entities --- */
typedef struct s_light
{
	t_point3		position;
	t_real			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	int				id;
	t_point3		position;
	t_vec3			direction;
	int				fov;
	t_real			viewport_width;
	t_real			viewport_height;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			lower_left_corner;
	struct s_camera	*next;
}	t_camera;

/* --- Graphics --- */
typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	t_real	inv_width;
	t_real	inv_height;
	t_real	aspect_ratio;
}	t_window;

/* --- Scene & Control --- */
typedef enum e_control_mode
{
	TRANSLATE,
	ROTATE
}	t_control_mode;

typedef struct s_scene
{
	t_window		mlx_window;
	t_image			frame_buffer;
	t_color			ambient;
	t_object		*objects;
	t_light			*lights;
	t_camera		*cameras;
	t_camera		*active_camera;
	t_object		*selected_object;
	t_light			*selected_light;
	t_control_mode	control_mode;
}	t_scene;

/* --- Dispatch --- */
typedef struct s_parse_map
{
	char		*id;
	t_status	(*func)(
		t_scene *scene,
		char **line_tokens);
}	t_parse_map;

typedef struct s_key_map
{
	int		keycode;
	t_bool	(*func)(
		t_scene *scene);
}	t_key_map;

typedef struct s_hit_map
{
	t_object_type	type;
	t_bool			(*func)(
		t_object *objects,
		t_ray *ray,
		t_hit_record *record);
}	t_hit_map;

typedef struct s_resize_map
{
	t_object_type	type;
	void			(*func)(
			t_object *object,
			int key);
}	t_resize_map;

typedef struct s_translate_map
{
	t_object_type	type;
	void			(*func)(
			t_object *object,
			t_vec3 transform);
}	t_translate_map;

typedef struct s_rotate_map
{
	t_object_type	type;
	void			(*func)(
			t_object *object,
			t_vec3 rot_axis);
}	t_rotate_map;

#endif