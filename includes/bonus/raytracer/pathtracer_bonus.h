/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtracer_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:21:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 16:46:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHTRACER_BONUS_H
# define PATHTRACER_BONUS_H

# include "../structs/s_scene_bonus.h"

t_vec3	random_cosine_dir(t_vec3 n, unsigned int *seed);
void	build_onb(t_vec3 n, t_vec3 *t, t_vec3 *b);
t_vec3	sample_ggx(t_vec3 n, t_real roughness, unsigned int *seed);
void	sample_rough_dielectric(t_material *m, t_vec3 n, t_vec3 v,
			t_path_info *info);
t_real	dielectric_bsdf_pdf(t_material *m, t_vec3 n, t_vec3 v, t_vec3 l);
t_real	power_heuristic(t_real pdf_a, t_real pdf_b);
t_color	eval_bsdf(t_material *mat, t_hit_record *rec, t_vec3 v, t_vec3 l);
t_real	bsdf_pdf(t_material *mat, t_vec3 n, t_vec3 v, t_vec3 l);
void	sample_bsdf(t_material *mat, t_vec3 n, t_vec3 v, t_path_info *info);
t_color	sample_direct_lighting(t_scene *s, t_hit_record *rec, t_vec3 v,
			t_path_info *info);
t_color	path_trace(t_scene *s, t_ray ray, unsigned int *seed);
t_bool	russian_roulette(t_path_info *info, t_real p);
t_color	debug_pathtracer(t_scene *s, t_hit_record *rec, t_path_info *i,
			t_ray *ray);
t_color	debug_light_contribution(t_light *l, t_hit_record *rec,
			t_path_info *info);
void	get_light_geometry(t_light *light, t_hit_record *record,
			unsigned int *seed, t_light_sample_vars *vars);
t_color	compute_light_contribution(t_light *l, t_hit_record *rec, t_vec3 v,
			t_path_info *info);
t_ray	update_ray(t_hit_record *rec, t_vec3 next_dir);
t_real	compute_emissive_pdf(t_hit_record *rec, t_vec3 ray_dir);
t_bool	is_color_finite(t_color *c);
t_bool	is_occulted(t_path_info *i, t_hit_record *rec, t_light_sample_vars *v);
t_real	emissive_area(t_object *obj);
t_vec3	sample_emissive_point(t_object *obj, unsigned int *seed);
t_color	compute_emissive_contribution(t_object *obj, t_hit_record *rec,
			t_vec3 v, t_path_info *info);

#endif