/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_emissive_contribution_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:46:28 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 17:02:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vec3	get_emissive_normal(t_object *obj, t_vec3 pt)
{
	if (obj->type == SPHERE)
		return (vec3_normalize(vec3_sub(pt, obj->u_data.sphere.center)));
	if (obj->type == DISK)
		return (obj->u_data.disk.normal);
	if (obj->type == TRIANGLE)
		return (obj->u_data.triangle.normal);
	return (obj->u_data.rectangle.normal);
}

static t_bool	get_emissive_geometry(t_object *obj, t_hit_record *rec,
		t_path_info *info, t_light_sample_vars *s)
{
	s->light_pos = sample_emissive_point(obj, &info->seed);
	s->light_dir = vec3_sub(s->light_pos, rec->hit_point);
	s->dist = vec3_len(s->light_dir);
	if (s->dist < EPSILON)
		return (FALSE);
	s->light_dir = vec3_normalize(s->light_dir);
	if (is_occulted(info, rec, s))
		return (FALSE);
	return (TRUE);
}

static t_real	emissive_nee_pdf(t_object *obj, t_light_sample_vars *s)
{
	t_vec3	sn;
	t_real	cos_l;
	t_real	area;

	sn = get_emissive_normal(obj, s->light_pos);
	cos_l = fabs(vec3_dot(vec3_scale(s->light_dir, -1.0), sn));
	if (cos_l < 0.01)
		cos_l = 0.01;
	area = emissive_area(obj);
	if (area < EPSILON)
		area = EPSILON;
	return ((s->dist * s->dist) / (area * cos_l + EPSILON));
}

t_color	compute_emissive_contribution(t_object *obj, t_hit_record *rec,
		t_vec3 v, t_path_info *info)
{
	t_light_sample_vars	s;
	t_real				n_dot_l;
	t_real				pdf;
	t_color				result;

	if (!get_emissive_geometry(obj, rec, info, &s))
		return ((t_color){0.0, 0.0, 0.0});
	n_dot_l = fmax(vec3_dot(rec->normal, s.light_dir), 0.0);
	if (n_dot_l <= EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	pdf = emissive_nee_pdf(obj, &s);
	if (pdf < EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	s.f_r = eval_bsdf(rec->object->material, rec, v, s.light_dir);
	s.weight = power_heuristic(pdf, bsdf_pdf(rec->object->material,
				rec->normal, v, s.light_dir));
	result = color_scale(color_prod(s.f_r, obj->material->emission_color),
			n_dot_l * s.weight / pdf);
	if (!is_color_finite(&result))
		return ((t_color){0.0, 0.0, 0.0});
	return (result);
}
