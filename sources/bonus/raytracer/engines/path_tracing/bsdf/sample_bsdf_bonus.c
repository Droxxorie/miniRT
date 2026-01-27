/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_bsdf_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:23:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/26 20:16:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	get_sample_weight(t_material *mat)
{
	if (mat->metallic >= 0.99)
		return (1.0);
	if (mat->roughness >= 0.99)
		return (0.0);
	return (0.5);
}

//* up_right[0] = up
//* up_right[1] = right
//* cos_sin_theta[0] = cos_theta
//* cos_sin_theta[1] = sin_theta
static t_vec3	sample_ggx(t_vec3 n, t_real roughness, unsigned int *seed)
{
	t_real	r[2];
	t_real	phi;
	t_real	cos_sin_theta[2];
	t_vec3	h_tangent;
	t_vec3	up_right[2];

	r[0] = random_double(seed);
	r[1] = random_double(seed);
	phi = TWO_PI * r[0];
	cos_sin_theta[0] = sqrt((1.0 - r[1]) / (1.0 + (roughness * roughness
					* roughness * roughness - 1.0) * r[1]));
	cos_sin_theta[1] = sqrt(1.0 - cos_sin_theta[0] * cos_sin_theta[0]);
	h_tangent = (t_vec3){cos_sin_theta[1] * cos(phi), cos_sin_theta[1]
		* sin(phi), cos_sin_theta[0]};
	build_onb(n, &up_right[0], &up_right[1]);
	return (vec3_normalize(vec3_add(vec3_add(vec3_scale(up_right[1],
						h_tangent.x), vec3_scale(up_right[0], h_tangent.y)),
				vec3_scale(n, h_tangent.z))));
}

//* pdf[0] = pdf_specular
//* pdf[1] = pdf_diffuse
t_real	bsdf_pdf(t_material *mat, t_vec3 n, t_vec3 v, t_vec3 l)
{
	t_real	pdf[2];
	t_real	specular_weight;
	t_vec3	h;
	t_real	d;

	if (mat->type == DIELECTRIC)
		return (0.0);
	if (mat->metallic < 0.01 && (mat->roughness >= 0.99))
		return (fmax(vec3_dot(n, l), 0.0) * INV_PI);
	h = vec3_normalize(vec3_add(v, l));
	d = distribution_ggx(n, h, mat->roughness);
	pdf[0] = (d * fmax(vec3_dot(n, h), 0.0)) / (4.0 * fmax(vec3_dot(v, h), 0.0)
			+ EPSILON);
	if (mat->metallic >= 0.99)
		return (pdf[0]);
	pdf[1] = fmax(vec3_dot(n, l), 0.0) * INV_PI;
	specular_weight = get_sample_weight(mat);
	return (specular_weight * pdf[0] + (1.0 - specular_weight) * pdf[1]);
}

static void	sample_dielectric(t_material *mat, t_vec3 r_in, t_vec3 n,
		t_path_info *info)
{
	t_vec3	outward_normal;
	t_vec3	refracted;
	t_real	ior_ratio;
	t_real	cosine;
	t_real	reflect_prob;

	outward_normal = n;
	ior_ratio = 1.0 / mat->ior;
	cosine = -vec3_dot(r_in, n) / vec3_len(r_in);
	if (vec3_dot(r_in, n) > 0.0)
	{
		outward_normal = vec3_scale(n, -1.0);
		ior_ratio = mat->ior;
		cosine = mat->ior * vec3_dot(r_in, n) / vec3_len(r_in);
	}
	if (vec_refract(r_in, outward_normal, ior_ratio, &refracted))
		reflect_prob = reflectance(cosine, mat->ior);
	else
		reflect_prob = 1.0;
	info->next_dir = refracted;
	if (random_double(&info->seed) < reflect_prob)
		info->next_dir = vec_reflect(r_in, n);
	info->pdf = 1.0;
	info->specular_bounce = TRUE;
}

void	sample_bsdf(t_material *mat, t_vec3 n, t_vec3 v, t_path_info *info)
{
	t_real	specular_weight;
	t_vec3	h;

	if (mat->type == DIELECTRIC || mat->ior > 1.0)
	{
		sample_dielectric(mat, vec3_scale(v, -1.0), n, info);
		return ;
	}
	specular_weight = get_sample_weight(mat);
	if (random_double(&info->seed) < specular_weight)
	{
		h = sample_ggx(n, mat->roughness, &info->seed);
		info->next_dir = vec_reflect(vec3_scale(v, -1.0), h);
		if (vec3_dot(info->next_dir, n) <= 0.0)
			info->pdf = 0.0;
		else
			info->pdf = bsdf_pdf(mat, n, v, info->next_dir);
		info->specular_bounce = TRUE;
	}
	else
	{
		info->next_dir = random_cosine_dir(n, &info->seed);
		info->pdf = bsdf_pdf(mat, n, v, info->next_dir);
		info->specular_bounce = FALSE;
	}
}
