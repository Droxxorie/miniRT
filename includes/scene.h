/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 23:08:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "macros.h"
# include "structures.h"

/* Setup */
t_status	load_scene(t_scene *scene, const char *file_path);
void		prepare_cameras(t_scene *scene);
void		setup_camera(t_camera *cam, t_real aspect_ratio);

/* Dispatchers */
void		dispatch_translate(t_object *obj, t_vec3 vec);
void		dispatch_rotate(t_object *obj, t_vec3 vec);
void		dispatch_resize(t_object *obj, int key);

/* Modifiers */
void		translate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		rotate_camera(t_camera *cam, t_vec3 vec, t_real ratio);
void		translate_light(t_light *light, t_vec3 vec);

void		translate_sphere(t_object *obj, t_vec3 vec);
void		translate_plane(t_object *obj, t_vec3 vec);
void		translate_cylinder(t_object *obj, t_vec3 vec);

void		rotate_plane(t_object *obj, t_vec3 vec);
void		rotate_cylinder(t_object *obj, t_vec3 vec);

void		resize_sphere(t_object *obj, int key);
void		resize_cylinder(t_object *obj, int key);

#endif