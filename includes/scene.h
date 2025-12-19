/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:36:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "macros.h"
# include "structures.h"

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
/* Setup */
t_status	load_scene(t_scene *scene, const char *file_path);
void		prepare_cameras(t_scene *scene);

/* Dispatchers */
void		dispatch_translate(t_object *obj, t_vec3 vec);
void		dispatch_rotate(t_object *obj, t_vec3 vec);
void		dispatch_resize(t_object *obj, int mode, int direction);

/* Modifiers */
void		update_object_matrix(t_object *object);
void		update_sphere_matrix(t_object *object);
void		update_plane_matrix(t_object *object);
void		update_cylinder_matrix(t_object *object);
void		update_camera_matrix(t_camera *camera, t_real aspect_ratio);

void		translate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		rotate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		translate_light(t_light *light, t_vec3 vec);

void		translate_sphere(t_object *obj, t_vec3 translation);
void		translate_plane(t_object *obj, t_vec3 translation);
void		translate_cylinder(t_object *obj, t_vec3 translation);

t_vec3		rotate_vector(t_vec3 vector, t_vec3 axis, t_real angle);
void		rotate_plane(t_object *obj, t_vec3 rotation_axis);
void		rotate_cylinder(t_object *obj, t_vec3 rotation_axis);

void		resize_sphere(t_object *obj, int mode, int direction);
void		resize_cylinder(t_object *obj, int mode, int direction);

#endif