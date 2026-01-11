/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 21:21:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "macros_bonus.h"
# include "structures_bonus.h"

//* ========================================================================= */
//*                                SETUP                                      */
//* ========================================================================= */
void		prepare_cameras(t_scene *scene);
t_status	load_scene(t_scene *scene, const char *file_path);

//* ========================================================================= */
//*                                SAVE STATE                                 */
//* ========================================================================= */
void		save_scene_state(t_scene *scene);

//* ========================================================================= */
//*                                RESET STATE                                */
//* ========================================================================= */
void		reset_scene_state(t_scene *scene);
void		reset_camera_state(t_camera *camera);
void		reset_light_state(t_light *light);
void		reset_object_state(t_object *object);

//* ========================================================================= */
//*                                DISPATCHERS                                */
//* ========================================================================= */
void		dispatch_resize(t_object *obj, int mode, int direction);

//* ========================================================================= */
//*                                UPDATE                                     */
//* ========================================================================= */
void		update_camera(t_camera *camera, t_real aspect_ratio);

//* ========================================================================= */
//*                                MODIFIERS                                  */
//* ========================================================================= */
void		set_transform(t_object *object, t_mat4 transform);
void		apply_rotation_to_matrix(t_object *object, t_mat4 rotation_matrix);

//* --- Translate --- */
void		translate_light(t_light *light, t_vec3 vec);
void		translate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		translate_object(t_object *obj, t_vec3 translation);

//* --- Rotate --- */
void		rotate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		rotate_object(t_object *obj, t_vec3 rotation_axis);

//* --- Resize --- */
void		resize_sphere(t_object *obj, int mode, int direction);
void		resize_cylinder(t_object *obj, int mode, int direction);
void		resize_rectangle(t_object *obj, int mode, int direction);
void		resize_disk(t_object *obj, int mode, int direction);
void		resize_triangle(t_object *obj, int mode, int direction);
void		resize_torus(t_object *obj, int mode, int direction);
void		resize_camera_fov(t_camera *camera, int mode, int direction);
void		resize_cone(t_object *obj, int mode, int direction);
void		resize_box(t_object *obj, int mode, int direction);

#endif