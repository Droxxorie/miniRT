/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:39:31 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 09:25:53 by eraad            ###   ########.fr       */
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

typedef enum e_control_mode
{
	TRANSLATE,
	ROTATE,
	NONE
} t_control_mode;

typedef struct s_hit_record
{
	t_object	*object;
	t_point3	hit_point;
	t_vec3		normal;
	t_real		t; //* root
	t_bool		front_face;
	t_color		color;
}	t_hit_record;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		width;
	int		height;
	int		endian;
}	t_image;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
	t_real	aspect_ratio;
}	t_window;

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

t_bool		hit_objects(t_object *objects, t_ray *ray, t_hit_record *record);
t_bool		hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *record);
t_bool		hit_plane(t_plane *plane, t_ray *ray, t_hit_record *record);
t_bool		hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *record);
t_status	render_scene(t_scene *scene);
t_status	render_frame(t_scene *scene);
void		get_ray(t_camera *camera, t_ray *ray, t_real u, t_real v);
t_color		get_ray_color(t_scene *scene, t_ray *ray);
void		set_face_normal(t_hit_record *record, t_ray *ray, t_vec3 outward_normal);
int			color_to_int(t_color color);
void		image_pixel_put(t_image *image, int x, int y, int color);
t_vec3		vec_reflect(t_vec3 i, t_vec3 n);
t_color		phong_light(t_scene *scene, t_hit_record *record, t_ray *ray);

#endif