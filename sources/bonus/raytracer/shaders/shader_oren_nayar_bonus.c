/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_oren_nayar_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:28:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/29 09:45:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	get_coeffs(t_material *material, t_real *a, t_real *b)
{
	t_real	roughness_sq;

	if (material && material->roughness > EPSILON)
	{
		*a = material->a;
		*b = material->b;
	}
	else
	{
		roughness_sq = 0.25;
		*a = 1.0 - (0.5 * roughness_sq / (roughness_sq + 0.33));
		*b = 0.45 * roughness_sq / (roughness_sq + 0.09);
	}
}

//* Opti trigo pour éviter acos
static t_real	get_angle_term(t_real n_dot_l, t_real n_dot_v)
{
	t_real	cos_alpha;
	t_real	cos_beta;
	t_real	sin_alpha;
	t_real	tan_beta;

	if (n_dot_l < n_dot_v)
	{
		cos_alpha = n_dot_l;
		cos_beta = n_dot_v;
	}
	else
	{
		cos_alpha = n_dot_v;
		cos_beta = n_dot_l;
	}
	sin_alpha = sqrt(fmax(0.0, 1.0 - (cos_alpha * cos_alpha)));
	tan_beta = sqrt(fmax(0.0, 1.0 - (cos_beta * cos_beta)));
	return (sin_alpha * (tan_beta / fmax(EPSILON, cos_beta)));
}

static t_real	get_gamma(t_vec3 normal, t_vec3 light_dir, t_vec3 view_dir,
		t_real terms[2])
{
	t_vec3	light_proj;
	t_vec3	view_proj;
	t_real	gamma;

	light_proj = vec3_normalize(vec3_sub(light_dir, vec3_scale(normal,
					terms[0])));
	view_proj = vec3_normalize(vec3_sub(view_dir, vec3_scale(normal,
					terms[1])));
	gamma = fmax(0.0, vec3_dot(view_proj, light_proj));
	return (gamma);
}

//* dirs[0] = light_dir
//* dirs[1] = view_dir
//* dirs[2] = normal
//* dots[0] = n_dot_l
//* dots[1] = n_dot_v
//* coeffs[0] = A
//* coeffs[1] = B
t_color	shader_oren_nayar(t_light *light, t_hit_record *rec, t_ray *ray,
		t_color albedo)
{
	t_vec3	dirs[3];
	t_real	dots[2];
	t_real	coeffs[2];
	t_real	dist;
	t_real	term;

	if (!light || !rec || !ray)
		return ((t_color){0.0, 0.0, 0.0});
	get_light_data(light, rec->hit_point, &dirs[0], &dist);
	dots[0] = vec3_dot(rec->normal, dirs[0]);
	if (dots[0] <= 0.0)
		return ((t_color){0.0, 0.0, 0.0});
	dirs[1] = vec3_scale(ray->direction, -1.0);
	dots[1] = vec3_dot(rec->normal, dirs[1]);
	get_coeffs(rec->object->material, &coeffs[0], &coeffs[1]);
	term = get_gamma(rec->normal, dirs[0], dirs[1], dots);
	term *= get_angle_term(dots[0], dots[1]);
	term = dots[0] * (coeffs[0] + coeffs[1] * term);
	term *= get_light_attenuation(light, dist) * get_spot_factor(light,
			dirs[0]);
	return (color_scale(color_prod(light->color, albedo), term
			* light->brightness));
}
