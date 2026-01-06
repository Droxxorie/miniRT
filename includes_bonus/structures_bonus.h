/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:30:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 17:06:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

# include <stdlib.h>

//* ========================================================================= */
//*                                BASIC TYPES                                */
//* ========================================================================= */
typedef double			t_real;
typedef int				t_status;
typedef int				t_bool;

//* ========================================================================= */
//*                                MATHS                                      */
//* ========================================================================= */
typedef struct s_vec3
{
	t_real				x;
	t_real				y;
	t_real				z;
}						t_vec3;

typedef t_vec3			t_point3;

typedef struct s_mat4
{
	t_real				m[4][4];
}						t_mat4;

typedef struct s_poly
{
	t_real				a;
	t_real				half_b;
	t_real				c;
	t_real				min;
	t_real				max;
	t_real				root1;
	t_real				root2;
}						t_poly;

typedef struct s_color
{
	t_real				r;
	t_real				g;
	t_real				b;
}						t_color;

//* ========================================================================= */
//*                                RAYTRACING                                 */
//* ========================================================================= */
typedef struct s_ray
{
	t_point3			origin;
	t_vec3				direction;
	t_real				min;
	t_real				max;
}						t_ray;

//* ========================================================================= */
//*                                OBJECTS                                    */
//* ========================================================================= */
typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}						t_object_type;

typedef struct s_sphere
{
	t_point3			center;
	t_real				radius;
}						t_sphere;

typedef struct s_plane
{
	t_point3			origin;
	t_vec3				normal;
}						t_plane;

typedef enum e_cylinder_element
{
	BODY,
	BOTTOM_CAP,
	TOP_CAP,
	NONE_ELEMENT
}						t_cylinder_element;
typedef struct s_cylinder_hit
{
	t_ray				ray;
	t_real				t;
	t_cylinder_element	type;
	t_poly				eq_vars;
}						t_cylinder_hit;

typedef struct s_cylinder
{
	t_point3			center;
	t_vec3				axis;
	t_real				radius;
	t_real				height;
}						t_cylinder;

typedef struct s_object
{
	t_object_type		type;
	t_color				color;
	t_mat4				transform;
	t_mat4				inverse;
	t_mat4				transposed_inverse;
	t_bool				visible;
	union
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
	} u_data;
	struct s_object		*next;
}						t_object;

typedef struct s_hit_record
{
	t_object			*object;
	t_point3			hit_point;
	t_vec3				normal;
	t_real				t;
	t_bool				front_face;
	t_color				color;
	t_bool				need_details;
}						t_hit_record;

//* ========================================================================= */
//*                                ENTITIES                                   */
//* ========================================================================= */
typedef struct s_light
{
	int					id;
	t_point3			position;
	t_real				brightness;
	t_color				color;
	t_bool				active;
	struct s_light		*next;
}						t_light;

typedef struct s_camera
{
	int					id;
	t_point3			position;
	t_vec3				direction;
	int					fov;
	t_mat4				camera_to_world;
	t_real				scale_factor;
	t_real				width;
	t_real				height;
	t_real				aspect_ratio;
	t_real				tilt;
	struct s_camera		*next;
}						t_camera;

//* ========================================================================= */
//*                                GRAPHICS                                   */
//* ========================================================================= */
typedef struct s_image
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}						t_image;

typedef struct s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					width;
	int					height;
	t_real				aspect_ratio;
}						t_window;

//* ========================================================================= */
//*                                SCENE & CONTROL                            */
//* ========================================================================= */
typedef enum e_control_mode
{
	TRANSLATE,
	ROTATE,
}						t_control_mode;

# define RESIZE_RADIUS 1
# define RESIZE_HEIGHT 2

typedef struct s_scene
{
	char				*line_ptr;
	int					line_number;
	t_window			mlx_window;
	t_image				frame_buffer;
	t_color				ambient;
	t_object			*objects;
	t_light				*lights;
	t_camera			*cameras;
	t_camera			*active_camera;
	t_object			*selected_object;
	t_light				*selected_light;
	t_control_mode		control_mode;
	t_bool				shift_pressed;
	pthread_mutex_t		line_mutex;
	int					next_line;
	t_bool				to_save;
	char				*save_file;
}						t_scene;

//* --- Multi-threading --- */
typedef struct s_thread_data
{
	int				thread_id;
	t_scene			*scene;
}						t_thread_data;

//* ========================================================================= */
//*                                DISPATCH                                   */
//* ========================================================================= */
typedef t_status		(*t_parse_func)(t_scene *scene, char **line_tokens);
typedef struct s_parse_map
{
	char				*id;
	t_parse_func		func;
}						t_parse_map;

typedef t_bool			(*t_key_func)(t_scene *scene);
typedef struct s_key_map
{
	int					keycode;
	t_key_func			func;
}						t_key_map;

typedef t_bool			(*t_hit_func)(t_object *objects, t_ray *ray,
				t_hit_record *record);
typedef struct s_hit_map
{
	t_object_type		type;
	t_hit_func			func;
}						t_hit_map;

typedef void			(*t_resize_func)(t_object *object, int mode,
				int direction);
typedef struct s_resize_map
{
	t_object_type		type;
	t_resize_func		func;
}						t_resize_map;

typedef void			(*t_translate_func)(t_object *object, t_vec3 transform);
typedef struct s_translate_map
{
	t_object_type		type;
	t_translate_func	func;
}						t_translate_map;

typedef void			(*t_rotate_func)(t_object *object, t_vec3 rot_axis);
typedef struct s_rotate_map
{
	t_object_type		type;
	t_rotate_func		func;
}						t_rotate_map;

#endif