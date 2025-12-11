/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:39:31 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:26:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <objects.h>
# include <entities.h>
# include <buffer.h>
# include <ray.h>

# define DEBUG_MODE_AABB "Displaying bounding boxes"
# define DEBUG_MODE_UNLIT "Displaying unlit colors"
# define DEBUG_MODE_FLAT "Displaying flat shading"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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
	t_object	*object; //? Un seul objet intersecté donc peut etre pas une liste
	t_point3	point;
	t_vec3		normal;
	t_real		t;
	t_bool		front_face;
	t_color		color;
}	t_hit_record;

typedef struct s_scene
{
	// char			*file; //? a supprimer/bouger
	// char			*line; //? a supprimer/bouger
	t_bool			bmp_saved; //? a voir si je garde
	// t_real			aspect_ratio; //* ex ratio
	t_window		mlx_window; //* ex mlx
	t_mode			render_mode; //*ex viewport
	t_buffer		frame_buffer; //* ex main
	t_real			completion; //? Inutile pour le moment
	t_real			prog_add; //? Same
	t_vec2			screen; //? doublon avec window width/height
	t_real			ambient;
	t_color 		ambient_color;
	t_object		*objects;
	t_light			*lights;
	// t_camera_list	*cameras;
	t_camera		*cameras;
	int				camera_count;
	int				u; //? var de rendu a deplacer
	int				v; //? var de rendu a deplacer
} t_scene;

#endif