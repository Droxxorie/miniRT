/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:38:53 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:19:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <graphics.h>

# define STEP_MOVE 1.0
# define STEP_ROT 0.1
# define STEP_SIZE 0.5

# define RIGHT_CLICK 1
# define LEFT_CLICK 2

# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ESC 53
# define KEY_TAB 48
# define KEY_SPACE 49

# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_W 13
# define KEY_Z 6
# define KEY_S 1
# define KEY_A 0
# define KEY_Q 12
# define KEY_D 2
# define KEY_E 14

# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define MASK_NO_EVENT 0L
# define MASK_KEY_PRESS (1L << 0)
# define MASK_KEY_RELEASE (1L << 1)
# define MASK_BUTTON_PRESS (1L << 2)
# define MASK_BUTTON_RELEASE (1L << 3)

//* resize
void	resize_sphere(t_object *object, int key);
void	resize_cylinder(t_object *object, int key);
void	dispatch_resize(t_object *object, int key);

//* translate
void	translate_sphere(t_object *object, t_vec3 translation);
void	translate_cylinder(t_object *object, t_vec3 translation);
void	translate_plane(t_object *object, t_vec3 translation);
void	translate_camera(t_camera *camera, t_vec3 translation,
			t_real aspect_ratio);
void	translate_light(t_object *object, t_vec3 translation);
void	dispatch_translate(t_object *object, t_vec3 translation);

//* rotate
void	rotate_cylinder(t_object *object, t_vec3 angles);
void	rotate_plane(t_object *object, t_vec3 angles);
void	rotate_camera(t_camera *camera, t_vec3 angles, t_real aspect_ratio);
void	dispatch_rotate(t_object *object, t_vec3 rot_axis);

int		mouse_hook(int button, int x, int y, t_scene *scene);
int		key_hook(int key, t_scene *scene);
t_vec3	get_input_vector(int key);
void	switch_camera_next(t_scene *scene);
t_bool	hit_light(t_light *light, t_ray *ray, t_real hit_radius);
void	action_camera(t_scene *scene, t_vec3 input_vector);
void	action_selection(t_scene *scene, t_vec3 input_vector);
int		close_window(t_scene *scene);
void	input_manager(t_scene *scene);

#endif