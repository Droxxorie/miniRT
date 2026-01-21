/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 22:40:33 by eraad            ###   ########.fr       */
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

void		get_box_uv(t_point3 p, t_vec3 n, t_real *u, t_real *v);
void		get_cone_uv(t_point3 p, t_cylinder_element type, t_real *u, t_real *v);
void		get_cylinder_uv(t_point3 p, t_cylinder_element type, t_real *u, t_real *v);
void		get_sphere_uv(t_point3 p, t_real *u, t_real *v);
void		get_torus_uv(t_point3 p, t_torus *torus,
				t_real *u, t_real *v);
void		get_disk_uv(t_point3 p, t_real *u, t_real *v);
void		get_rectangle_uv(t_point3 p, t_real *u, t_real *v);

//* ========================================================================= */
//*                                LIGHTING                                   */
//* ========================================================================= */
t_vec3		vec_reflect(t_vec3 i, t_vec3 n);
t_real		reflectance(t_real cosine, t_real ref_index);
t_vec3		vec_refract(t_vec3 uv, t_vec3 n, t_real ni_over_nt);

t_color		cast_ray(t_scene *scene, t_ray *ray, int depth);
t_ray		new_ray(t_point3 origin, t_vec3 direction);
// t_color		phong_light(t_scene *scene, t_hit_record *record, t_ray *ray);
t_real		compute_ao(t_scene *scene, t_hit_record *record);
t_real		get_shadow_factor(t_scene *scene, t_hit_record *record,
				t_light *light);
t_color		compute_diffuse(t_light *light, t_hit_record *record,
				t_color albedo);

//* ========================================================================= */
//*                                SHADERS                                    */
//* ========================================================================= */
t_color		get_albedo(t_material *mat, t_hit_record *record);
t_real		get_shininess(t_material *mat, t_hit_record *record);
t_color		shader_phong(t_scene *scene, t_hit_record *record, t_ray *ray);
t_color		sample_texture(t_image *texture, t_real u, t_real v);
t_color		render_shade(t_scene *scene, t_hit_record *record, t_ray *ray,
				int depth);
t_color		render_debug(t_scene *scene, t_hit_record *record);
t_color		shader_metal(t_scene *scene, t_hit_record *record, t_ray *ray,
				int depth);
t_color		shader_dielectric(t_scene *scene, t_hit_record *record, t_ray *ray,
				int depth);
t_color		shader_lambert(t_scene *scene, t_hit_record *record,
				t_color albedo);

//* ========================================================================= */
//*                                RAYTRACING                                 */
//* ========================================================================= */
t_point3	ray_at(t_ray *ray, t_real t);
t_ray		transform_ray(t_ray ray, t_mat4 inverse);
void		generate_ray(t_camera *camera, t_ray *ray, t_real x, t_real y);
void		set_face_normal(t_hit_record *record, t_ray *ray,
				t_vec3 outward_normal);

#endif