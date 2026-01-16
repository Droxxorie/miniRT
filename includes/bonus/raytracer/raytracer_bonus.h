/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 17:17:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_BONUS_H
# define RAYTRACER_BONUS_H

# include "../structs/s_scene_bonus.h"

//* ========================================================================= */
//*                                INTERSECTIONS                              */
//* ========================================================================= */
t_bool		hit_dispatch(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		ray_tracing(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_box(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_cone(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_disk(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_torus(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_sphere(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_cylinder(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_triangle(t_object *object, t_ray *ray, t_hit_record *record);
t_bool		hit_rectangle(t_object *object, t_ray *ray, t_hit_record *record);

//* ========================================================================= */
//*                                LIGHTING                                   */
//* ========================================================================= */
t_vec3		vec_reflect(t_vec3 i, t_vec3 n);
t_color		compute_pixel_color(t_scene *scene, t_ray *ray);
t_color		phong_light(t_scene *scene, t_hit_record *record, t_ray *ray);
t_real		compute_ao(t_scene *scene, t_point3 point, t_vec3 normal);
t_real		get_shadow_factor(t_scene *scene, t_hit_record *record,
				t_light *light);

//* ========================================================================= */
//*                                RAYTRACING                                 */
//* ========================================================================= */
t_point3	ray_at(t_ray *ray, t_real t);
t_ray		transform_ray(t_ray ray, t_mat4 inverse);
void		generate_ray(t_camera *camera, t_ray *ray, t_real x, t_real y);
void		set_face_normal(t_hit_record *record, t_ray *ray,
				t_vec3 outward_normal);

#endif