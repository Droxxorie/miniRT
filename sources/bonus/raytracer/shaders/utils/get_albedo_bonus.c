/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_albedo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:42:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 14:10:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	get_albedo(t_material *mat, t_hit_record *record)
{
	if (record->object->is_fractal == TRUE)
		return (record->color);
	if (mat && mat->albedo_map)
		return (sample_texture(mat->albedo_map, record->u, record->v));
	if (mat->pattern_type == PATTERN_CHECKER)
		return (pattern_checker(record, mat));
	if (mat->pattern_type == PATTERN_RAINBOW)
		return (pattern_rainbow(record));
	if (mat->pattern_type == PATTERN_WAVE)
		return (pattern_wave(record, mat));
	if (mat->pattern_type == PATTERN_PERLIN_NOISE)
		return (pattern_perlin_noise(record, mat));
	if (mat->pattern_type == PATTERN_MARBLE)
		return (pattern_marble(record, mat));
	if (mat)
		return (mat->color);
	return (record->color);
}

static void	apply_normal_map(t_hit_record *rec, t_material *mat)
{
	t_color	pixel;
	t_vec3	map_n;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	up;

	if (!mat || !mat->normal_map)
		return ;
	pixel = sample_texture(mat->normal_map, rec->u, rec->v);
	map_n = (t_vec3){(pixel.r * 2.0f) - 1.0f, -((pixel.g * 2.0f) - 1.0f),
		fabsf((pixel.b * 2.0f) - 1.0f)};
	if (fabsf(rec->normal.y) < 0.999f)
		up = (t_vec3){0.0f, 1.0f, 0.0f};
	else
		up = (t_vec3){1.0f, 0.0f, 0.0f};
	tangent = vec3_normalize(vec3_cross(up, rec->normal));
	bitangent = vec3_normalize(vec3_cross(rec->normal, tangent));
	rec->normal = vec3_normalize(vec3_add(vec3_add(vec3_scale(tangent, map_n.x),
					vec3_scale(bitangent, map_n.y)), vec3_scale(rec->normal,
					map_n.z)));
}

void	prepare_surface(t_hit_record *rec)
{
	t_material	*mat;

	mat = rec->object->material;
	if (!mat)
		return ;
	if (mat->uv_scale > EPSILON)
	{
		rec->u *= mat->uv_scale;
		rec->v *= mat->uv_scale;
	}
	apply_normal_map(rec, mat);
	rec->albedo = get_albedo(mat, rec);
	rec->roughness = mat->roughness;
	rec->metallic = mat->metallic;
	if (mat->roughness_map)
		rec->roughness = sample_texture(mat->roughness_map, rec->u, rec->v).r;
	if (mat->metallic_map)
		rec->metallic = sample_texture(mat->metallic_map, rec->u, rec->v).r;
	rec->f0 = (t_color){0.04, 0.04, 0.04};
	if (rec->metallic > 0.5)
		rec->f0 = mat->specular_color;
	else if (rec->roughness > 0.99)
		rec->f0 = (t_color){0.0, 0.0, 0.0};
}
