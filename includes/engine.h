/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:39:31 by eraad             #+#    #+#             */
/*   Updated: 2025/12/09 20:24:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <shapes.h>
# include <entities.h>
# include <buffer.h>
# include <ray.h>

# define DEBUG_MODE_AABB "Displaying bounding boxes"
# define DEBUG_MODE_UNLIT "Displaying unlit colors"
# define DEBUG_MODE_FLAT "Displaying flat shading"

typedef enum e_mode
{
	UNLIT,
	FLAT,
	SHADED,
	AABB,
	NONE
}	t_mode;

typedef struct s_hit_record
{
	t_ray		ray; //? redondant, on verra
	t_shapes	*object; //? Un seul objet intersecté donc peut etre pas une liste
	t_point3	point;
	t_vec3		normal;
	t_real		t;
	t_bool		frontface;
	t_color		color;
}	t_hit_record;

typedef struct s_scene
{
	char			*file; //? pk ici ?
	char			*line; //? pk ici ?
	t_bool			bmp_saved; //?
	t_real			aspect_ratio; //* ex ratio
	t_window		mlx_window; //* ex mlx
	t_mode			render_mode; //*ex viewport
	t_buffer		frame_buffer; //* ex main
	t_real			completion; //?
	t_real			prog_add; //?
	t_vec2			screen; //? kesako exacetement
	t_real			ambient; //?
	t_color 		ambient_color; //?
	t_shapes		*shapes;
	t_lights		*lights;
	t_camera_list	*cameras;
	t_camera		*current_camera; //? autant juste utiliser camera_list->camera ?
	int				camera_count;
	int				camera_id; //? Pourquoi, déjà dans camera_list
	int				u; //?
	int				v; //?
} t_scene;

#endif