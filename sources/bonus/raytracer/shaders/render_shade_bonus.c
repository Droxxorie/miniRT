/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shade_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:35:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 11:47:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	map_n = (t_vec3){(pixel.r * 2.0) - 1.0, (pixel.g * 2.0) - 1.0, (pixel.b
			* 2.0) - 1.0};
	if (fabs(rec->normal.y) < 0.999)
		up = (t_vec3){0, 1, 0};
	else
		up = (t_vec3){1, 0, 0};
	tangent = vec3_normalize(vec3_cross(up, rec->normal));
	bitangent = vec3_normalize(vec3_cross(rec->normal, tangent));
	rec->normal = vec3_normalize(vec3_add(vec3_add(vec3_scale(tangent, map_n.x),
					vec3_scale(bitangent, map_n.y)), vec3_scale(rec->normal,
					map_n.z)));
}

static t_color	mix_reflection(t_scene *scene, t_hit_record *record, t_ray *ray,
		int depth)
{
	t_color	diffuse;
	t_color	reflected;
	t_real	factor;

	factor = sample_texture(record->object->material->metallic_map, record->u,
			record->v).r;
	diffuse = shader_lambert(scene, record, get_albedo(record->object->material,
				record));
	reflected = shader_metal(scene, record, ray, depth);
	return (color_mix(diffuse, reflected, factor));
}

static void	scale_uv_apply_normal(t_hit_record *record, t_material *mat)
{
	if (mat)
	{
		if (mat->uv_scale > EPSILON)
		{
			record->u *= mat->uv_scale;
			record->v *= mat->uv_scale;
		}
		apply_normal_map(record, mat);
	}
}

//* Lambert : diffuse only shader
//* Blinn-Phong : diffuse + specular highlights
//* Metal : reflective shader with roughness
//* Dielectric : transparent shader with refraction
//* Oren-Nayar : diffuse shader for rough surfaces
//* Cook-Torrance : physically based shader with microfacet model
t_color	render_shade(t_scene *s, t_hit_record *rec, t_ray *ray, int depth)
{
	t_material	*mat;

	mat = rec->object->material;
	scale_uv_apply_normal(rec, mat);
	if (!mat)
		return (shader_lambert(s, rec, rec->object->color));
	if (mat && (color_mean(mat->emission_color) > EPSILON))
	{
		if (mat->emission_map)
			return (sample_texture(mat->emission_map, rec->u, rec->v));
		return (mat->emission_color);
	}
	if (mat->type == COOK_TORRANCE)
		return (shader_cook_torrance(s, rec, ray));
	if (mat->type == METAL && depth > 0)
		return (shader_metal(s, rec, ray, depth));
	if (mat->type == DIELECTRIC && depth > 0)
		return (shader_dielectric(s, rec, ray, depth));
	if (mat->type == OREN_NAYAR)
		return (shader_oren_nayar(s->lights, rec, ray, get_albedo(mat, rec)));
	if (mat->type == PHONG)
		return (shader_phong(s, rec, ray));
	if (mat->metallic_map && depth > 0)
		return (mix_reflection(s, rec, ray, depth));
	return (shader_lambert(s, rec, get_albedo(mat, rec)));
}
