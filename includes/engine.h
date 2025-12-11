/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:39:31 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 22:29:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <entities.h>
# include <objects.h>
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
}				t_mode;

typedef struct s_hit_record
{
	t_object	*object;
	t_point3	point;
	t_vec3		normal;
	t_real		t; //* root
	t_bool		front_face;
	t_color		color;
}				t_hit_record;

typedef struct s_image
{
	void		*ptr;
	char		*addr;
	int			bpp; // bits per pixel
	// int		size; //? A voir plus tard
	int			line_len;
	int			width; //* pour bonus
	int			height;
	int			endian;
}				t_image;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			width;
	int			height;
	t_real		aspect_ratio;
}				t_window;

typedef enum e_buftype
{
	BUFFER_MISSIING,
	BUFFER_IMAGE,
	BUFFER_TEXTURE,
	BUFFER_FILTER,
	BUFFER_DEBUG
}				t_buftype;

typedef struct s_scene
{
	// char		*file; //? a supprimer/bouger
	// char		*line; //? a supprimer/bouger
	t_bool		bmp_saved; //? a voir si je garde
	// t_real		aspect_ratio; //* ex ratio
	t_window	mlx_window;  //* ex mlx
	t_mode		render_mode;   //*ex viewport
	t_image		frame_buffer; //* ex main
	t_real		completion;    //? Inutile pour le moment
	t_real		prog_add;      //? Same
	t_vec2		screen;        //? doublon avec window width/height
	t_color		ambient;
	t_object	*objects;
	t_light		*lights;
	t_camera	*cameras;
	int			camera_count;
	int			u; //? var de rendu a deplacer
	int			v; //? var de rendu a deplacer
}				t_scene;

t_bool		hit_objects(t_object *objects, t_ray *ray, t_hit_record *record);
t_status	render_scene(t_scene *scene, int x, int y, t_real u, t_real v);
t_status	render_frame(t_scene *scene);
void		get_ray(t_camera *camera, t_ray *ray, t_real u, t_real v);


#endif