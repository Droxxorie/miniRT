/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 18:57:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "macros.h"
# include "structures.h"

//* ========================================================================= */
//*                                SETUP                                      */
//* ========================================================================= */
void		prepare_cameras(t_scene *scene);
t_status	load_scene(t_scene *scene, const char *file_path);

//* ========================================================================= */
//*                                DISPATCHERS                                */
//* ========================================================================= */
void		dispatch_rotate(t_object *obj, t_vec3 vec);
void		dispatch_translate(t_object *obj, t_vec3 vec);
void		dispatch_resize(t_object *obj, int mode, int direction);

//* ========================================================================= */
//*                                MODIFIERS                                  */
//* ========================================================================= */
void		set_transform(t_object *object, t_mat4 transform);
void		apply_rotation_to_matrix(t_object *object, t_mat4 rotation_matrix);

//* --- Update matrices --- */
void		update_plane_matrix(t_object *object);
void		update_object_matrix(t_object *object);
void		update_sphere_matrix(t_object *object);
void		update_cylinder_matrix(t_object *object);
void		update_camera_matrix(t_camera *camera, t_real aspect_ratio);

//* --- Translate --- */
void		translate_light(t_light *light, t_vec3 vec);
void		translate_plane(t_object *obj, t_vec3 translation);
void		translate_sphere(t_object *obj, t_vec3 translation);
void		translate_cylinder(t_object *obj, t_vec3 translation);
void		translate_camera(t_camera *cam, t_vec3 vec, t_real ratio);

//* --- Rotate --- */
void		rotate_plane(t_object *obj, t_vec3 rotation_axis);
void		rotate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		rotate_cylinder(t_object *obj, t_vec3 rotation_axis);
t_vec3		rotate_vector(t_vec3 vector, t_vec3 axis, t_real angle);

//* --- Resize --- */
void		resize_sphere(t_object *obj, int mode, int direction);
void		resize_cylinder(t_object *obj, int mode, int direction);

#endif