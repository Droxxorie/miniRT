/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:29:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/26 21:11:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	init_cook_torrance_vars(t_cook_torrance_vars *v, t_hit_record *rec,
		t_ray *ray, int depth)
{
	t_material	*mat;

	mat = rec->object->material;
	v->depth = depth;
	v->n = rec->normal;
	v->v = vec3_scale(ray->direction, -1.0);
	v->n_dot_v = fmax(vec3_dot(v->n, v->v), 0.0);
	v->albedo = get_albedo(mat, rec);
	v->roughness = mat->roughness;
	v->metallic = mat->metallic;
	if (mat->roughness_map)
		v->roughness = sample_texture(mat->roughness_map, rec->u, rec->v).r;
	if (mat->metallic_map)
		v->metallic = sample_texture(mat->metallic_map, rec->u, rec->v).r;
	v->f0 = (t_color){0.04, 0.04, 0.04};
	if (color_mean(mat->specular_color) > EPSILON)
		v->f0 = mat->specular_color;
	else if (v->metallic > 0.5)
		v->f0 = v->albedo;
}

t_real	distribution_ggx(t_vec3 n, t_vec3 h, t_real roughness)
{
	t_real	a_sq;
	t_real	n_dot_h;
	t_real	n_dot_h_sq;
	t_real	denom;
	t_real	num;

	a_sq = roughness * roughness * roughness * roughness;
	n_dot_h = fmax(vec3_dot(n, h), 0.0);
	n_dot_h_sq = n_dot_h * n_dot_h;
	num = a_sq;
	denom = (n_dot_h_sq * (a_sq - 1.0) + 1.0);
	denom = PI * denom * denom;
	return (num / fmax(denom, EPSILON));
}

static t_real	geometry_schlick(t_real n_dot_v, t_real roughness)
{
	t_real	r;
	t_real	k;

	r = roughness + 1.0;
	k = (r * r) / 8.0;
	return (n_dot_v / (n_dot_v * (1.0 - k) + k));
}

t_real	geometry_smith(t_vec3 n, t_vec3 v, t_vec3 l, t_real roughness)
{
	t_real	n_dot_v;
	t_real	n_dot_l;
	t_real	ggx1;
	t_real	ggx2;

	n_dot_v = fmax(vec3_dot(n, v), 0.0);
	n_dot_l = fmax(vec3_dot(n, l), 0.0);
	ggx1 = geometry_schlick(n_dot_v, roughness);
	ggx2 = geometry_schlick(n_dot_l, roughness);
	return (ggx1 * ggx2);
}

t_color	fresnel_schlick(t_real cos_theta, t_color f0)
{
	t_real	scale;
	t_color	result;

	scale = pow(1.0 - cos_theta, 5.0);
	result.r = f0.r + (1.0 - f0.r) * scale;
	result.g = f0.g + (1.0 - f0.g) * scale;
	result.b = f0.b + (1.0 - f0.b) * scale;
	return (result);
}
