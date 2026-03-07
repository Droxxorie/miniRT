/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_rough_dielectric_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:41:57 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 17:42:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	dielectric_f(t_real cos_i, t_real ior)
{
	t_real	f0;

	f0 = (1.0 - ior) / (1.0 + ior);
	f0 = f0 * f0;
	return (f0 + (1.0 - f0) * powf(1.0 - cos_i, 5.0));
}

static t_vec3	rd_choose_dir(t_vec3 v, t_vec3 h,
		t_real *params, unsigned int *seed)
{
	t_vec3	inc;
	t_vec3	refracted;
	t_real	fresnel;

	inc = vec3_scale(v, -1.0);
	fresnel = dielectric_f(fabsf(vec3_dot(v, h)), params[1]);
	if (random_double(seed) < fresnel
		|| !vec_refract(inc, h, params[0], &refracted))
		return (vec_reflect(inc, h));
	return (refracted);
}

static void	rd_compute_weight(t_vec3 *vecs, t_vec3 h,
		t_real roughness, t_path_info *info)
{
	t_real	dots[4];
	t_real	k;

	dots[0] = fmaxf(fabsf(vec3_dot(vecs[1], h)), EPSILON);
	dots[1] = fmaxf(fabsf(vec3_dot(vecs[0], vecs[1])), EPSILON);
	dots[2] = fmaxf(fabsf(vec3_dot(vecs[0], h)), EPSILON);
	dots[3] = fmaxf(fabsf(vec3_dot(vecs[0], info->next_dir)), EPSILON);
	k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
	info->bsdf_weight = (dots[1] / (dots[1] * (1.0 - k) + k))
		* (dots[3] / (dots[3] * (1.0 - k) + k))
		* dots[0] / (dots[1] * dots[2]);
	info->pdf = distribution_ggx(vecs[0], h, roughness)
		* dots[2] / (4.0 * dots[0] + EPSILON);
}

t_real	dielectric_bsdf_pdf(t_material *mat, t_vec3 n,
		t_vec3 v, t_vec3 l)
{
	t_vec3	h;
	t_real	d;
	t_real	dots[2];
	t_real	fresnel;

	if (fmaxf(vec3_dot(n, l), 0.0) <= EPSILON)
		return (0.0);
	h = vec3_normalize(vec3_add(v, l));
	d = distribution_ggx(n, h, mat->roughness);
	dots[0] = fmaxf(vec3_dot(n, h), 0.0);
	dots[1] = fmaxf(vec3_dot(v, h), EPSILON);
	fresnel = dielectric_f(dots[1], mat->ior);
	return (fresnel * d * dots[0] / (4.0 * dots[1] + EPSILON));
}

void	sample_rough_dielectric(t_material *mat, t_vec3 n,
		t_vec3 v, t_path_info *info)
{
	t_vec3	h;
	t_real	params[2];
	t_vec3	vecs[2];

	h = sample_ggx(n, mat->roughness, &info->seed);
	if (vec3_dot(v, h) < 0.0)
		h = vec3_scale(h, -1.0);
	if (info->front_face)
		params[0] = 1.0 / mat->ior;
	else
		params[0] = mat->ior;
	params[1] = mat->ior;
	info->next_dir = rd_choose_dir(v, h, params, &info->seed);
	if (fabsf(vec3_dot(n, info->next_dir)) < EPSILON)
	{
		info->pdf = 0.0;
		return ;
	}
	info->specular_bounce = FALSE;
	vecs[0] = n;
	vecs[1] = v;
	rd_compute_weight(vecs, h, mat->roughness, info);
}
