/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:18:56 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 15:28:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	debug_direct_light(t_scene *s, t_hit_record *rec,
		t_path_info *i, t_ray *ray)
{
	t_color	direct_light;

	if (!rec->object->material)
		return ((t_color){0, 0, 0});
	if (rec->object->material->emission_color.r > EPSILON
		|| rec->object->material->emission_color.g > EPSILON
		|| rec->object->material->emission_color.b > EPSILON)
		return (rec->object->material->emission_color);
	direct_light = sample_direct_lighting(s, rec, vec3_scale(ray->direction,
				-1.0), i);
	return (direct_light);
}

t_color	debug_pathtracer(t_scene *s, t_hit_record *rec, t_path_info *i,
		t_ray *ray)
{
	t_vec3	n_color;
	t_real	depth_val;

	if (s->render_mode == RENDER_NORMAL)
	{
		n_color = vec3_scale(vec3_add(rec->normal, (t_vec3){1, 1, 1}), 0.5);
		return ((t_color){n_color.x, n_color.y, n_color.z});
	}
	else if (s->render_mode == RENDER_DEPTH)
	{
		depth_val = 1.0 - (rec->t / 30.0);
		if (depth_val < 0)
			depth_val = 0;
		return ((t_color){depth_val, depth_val, depth_val});
	}
	else if (s->render_mode == RENDER_ALBEDO)
		return (get_albedo(rec->object->material, rec));
	else if (s->render_mode == RENDER_SHADOWS)
		return (debug_direct_light(s, rec, i, ray));
	return ((t_color){0.0, 0.0, 0.0});
}

t_color	debug_light_contribution(t_light *l, t_hit_record *rec,
		t_path_info *info)
{
	t_light_sample_vars	s;
	t_ray				s_ray;
	t_hit_record		s_rec;

	get_light_geometry(l, rec, &info->seed, &s);
	s_ray = new_ray(vec3_add(rec->hit_point, vec3_scale(rec->normal, 0.1)),
			s.light_dir);
	s_ray.min = 0.01;
	s_ray.is_shadow_ray = TRUE;
	s_ray.max = s.dist - 0.1;
	if (hit_bvh(info->bvh_root, &s_ray, &s_rec))
	{
		if (s_rec.object->material
			&& (s_rec.object->material->emission_color.r > EPSILON
				|| s_rec.object->material->emission_color.g > EPSILON
				|| s_rec.object->material->emission_color.b > EPSILON))
			return ((t_color){0, 0, 1});
		if (s_rec.t < 0.5)
			return ((t_color){1, 0, 0});
		return ((t_color){1, 1, 0});
	}
	return ((t_color){0, 1, 0});
}
