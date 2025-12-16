/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:29 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 23:08:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "macros.h"
# include "structures.h"

void	get_ray(t_camera *camera, t_ray *ray, t_real u, t_real v);
t_color	get_ray_color(t_scene *scene, t_ray *ray);
t_bool	hit_objects(t_object *objs, t_ray *ray, t_hit_record *record);
t_bool	hit_sphere(t_object *object, t_ray *ray, t_hit_record *record);
t_bool	hit_plane(t_object *object, t_ray *ray, t_hit_record *record);
t_bool	hit_cylinder(t_object *object, t_ray *ray, t_hit_record *record);
t_color	phong_light(t_scene *scene, t_hit_record *record, t_ray *ray);
t_vec3	vec_reflect(t_vec3 i, t_vec3 n);
void	set_face_normal(t_hit_record *record, t_ray *ray,
			t_vec3 outward_normal);

#endif