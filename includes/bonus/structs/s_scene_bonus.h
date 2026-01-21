/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_scene_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:52:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:36:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SCENE_BONUS_H
# define S_SCENE_BONUS_H

# include "s_object_bonus.h"
# include <pthread.h>

typedef struct s_light
{
	int				id;
	t_point3		position;
	t_real			brightness;
	t_point3		initial_position;
	t_real			initial_brightness;
	t_color			color;
	t_bool			active;
	struct s_light	*next;
}					t_light;

typedef struct s_camera
{
	int				id;
	t_point3		position;
	t_vec3			direction;
	t_real			fov;
	t_mat4			camera_to_world;
	t_real			scale_factor;
	t_real			width;
	t_real			height;
	t_real			aspect_ratio;
	t_real			tilt;
	t_point3		initial_position;
	t_vec3			initial_direction;
	int				initial_fov;
	t_real			initial_tilt;
	struct s_camera	*next;
}					t_camera;

typedef struct s_image
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	t_real			aspect_ratio;
}					t_window;

typedef enum e_control_mode
{
	TRANSLATE,
	ROTATE,
}					t_control_mode;

typedef enum e_render_mode
{
	RENDER_SHADE,
	RENDER_NORMAL,
	RENDER_AO,
	RENDER_UV,
	RENDER_DEPTH,
	RENDER_SHADOWS,
	RENDER_OBJECT_ID,
}					t_render_mode;

# define RESIZE_NONE -1
# define RESIZE_UNIFORM 0
# define RESIZE_X 1
# define RESIZE_Y 2
# define RESIZE_Z 3

typedef struct s_scene
{
	char			*file_name;
	char			*line_ptr;
	int				line_number;
	t_window		mlx_window;
	t_image			frame_buffer;
	t_color			ambient;
	t_object		*objects;
	t_bvh_node		*bvh_root;
	t_light			*lights;
	t_camera		*cameras;
	t_camera		*active_camera;
	t_object		*selected_object;
	t_light			*selected_light;
	t_control_mode	control_mode;
	t_bool			shift_pressed;
	t_bool			ctrl_pressed;
	t_bool			alt_pressed;
	pthread_mutex_t	line_mutex;
	int				next_line;
	t_bool			to_save;
	char			*save_file;
	t_render_mode	render_mode;
	t_material		*materials;
}					t_scene;

typedef struct s_thread_data
{
	int				thread_id;
	t_scene			*scene;
}					t_thread_data;

//* ========================================================================= */
//*                                DISPATCH                                   */
//* ========================================================================= */
// typedef t_status	(*t_parse_func)(t_scene *scene, char **line_tokens);
// typedef struct s_parse_map
// {
// 	char			*id;
// 	t_parse_func	func;
// }					t_parse_map;

typedef void		(*t_resize_func)(t_object *object, t_camera *camera,
			int mode, int direction);
typedef struct s_resize_map
{
	t_object_type	type;
	t_resize_func	func;
}					t_resize_map;

#endif