/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:38:53 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:40:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <engine.h>

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

#define KEY_1 18
#define KEY_2 19
#define KEY_3 20
#define KEY_4 21
#define KEY_5 23
#define KEY_6 22
#define KEY_7 26
#define KEY_8 28
#define KEY_9 25


//* resize
void	resize_sphere(t_object *object, int key);
void	resize_cylinder(t_object *object, int key);
void	dispatch_resize(t_object *object, int key);

//* translate
void	translate_sphere(t_object *object, t_vec3 translation);
void	translate_cylinder(t_object *object, t_vec3 translation);
void	translate_plane(t_object *object, t_vec3 translation);
void	dispatch_translate(t_object *object, t_vec3 translation);

//* rotate
void	rotate_cylinder(t_object *object, t_vec3 angles);
void	rotate_plane(t_object *object, t_vec3 angles);
void	dispatch_rotate(t_object *object, t_vec3 rot_axis);


int		mouse_hook(int button, int x, int y, t_scene *scene);
void	rotate_object(t_object *object, t_vec3 rot_axis);
void	translate_object(t_object *object, t_vec3 translation);

#endif