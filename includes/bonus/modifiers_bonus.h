/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:44:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 13:57:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODIFIERS_BONUS_H
# define MODIFIERS_BONUS_H

# include "structs/s_scene_bonus.h"

void	set_transform(t_object *object, t_mat4 transform);
void	dispatch_resize(t_object *obj, int mode, int direction);

//* ========================================================================= */
//*                                TRANSLATE                                  */
//* ========================================================================= */
void	translate_light(t_light *light, t_vec3 vec);
void	translate_object(t_object *obj, t_vec3 translation);
void	translate_camera(t_camera *cam, t_vec3 vec, t_real ratio);

//* ========================================================================= */
//*                                ROTATE                                     */
//* ========================================================================= */
void	rotate_object(t_object *obj, t_vec3 rotation_axis);
void	rotate_camera(t_camera *cam, t_vec3 vec, t_real ratio);

//* ========================================================================= */
//*                                RESIZE                                     */
//* ========================================================================= */
void	resize_box(t_object *obj, int mode, int direction);
void	resize_disk(t_object *obj, int mode, int direction);
void	resize_cone(t_object *obj, int mode, int direction);
void	resize_torus(t_object *obj, int mode, int direction);
void	resize_sphere(t_object *obj, int mode, int direction);
void	resize_cylinder(t_object *obj, int mode, int direction);
void	resize_triangle(t_object *obj, int mode, int direction);
void	resize_rectangle(t_object *obj, int mode, int direction);
void	resize_camera_fov(t_camera *camera, int mode, int direction);
void	resize_mandelbulb(t_object *object, int mode, int direction);
void	resize_menger_sponge(t_object *object, int mode, int direction);

#endif