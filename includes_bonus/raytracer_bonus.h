/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 19:37:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_BONUS_H
# define RAYTRACER_BONUS_H

# include "macros_bonus.h"
# include "structures_bonus.h"

//* ========================================================================= */
//*                                INTERSECTIONS                              */
//* ========================================================================= */
t_bool		hit_anything(t_object *objs, t_ray *ray);
t_bool		hit_objects(t_object *objs, t_ray *ray, t_hit_record *record);
t_bool		hit_plane(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_sphere(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_cylinder(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_rectangle(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_disk(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_triangle(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_torus(t_object *object, t_ray *ray, t_hit_record *record);

//* ========================================================================= */
//*                                LIGHTING                                   */
//* ========================================================================= */
t_vec3		vec_reflect(t_vec3 i, t_vec3 n);
t_color		compute_pixel_color(t_scene *scene, t_ray *ray);
t_color		phong_light(t_scene *scene, t_hit_record *record, t_ray *ray);

//* ========================================================================= */
//*                                RAYTRACING                                 */
//* ========================================================================= */
t_ray		transform_ray(t_ray ray, t_mat4 inverse);
t_point3	ray_at(t_ray *ray, t_real t);
void		generate_ray(t_camera *camera, t_ray *ray, t_real x, t_real y);
void		set_face_normal(t_hit_record *record, t_ray *ray,
				t_vec3 outward_normal);

#endif