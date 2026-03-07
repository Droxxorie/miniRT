/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optic_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:40:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/25 19:38:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* R = I - 2(I·N)N
t_vec3	vec_reflect(t_vec3 i, t_vec3 n)
{
	return (vec3_sub(i, vec3_scale(n, 2.0 * vec3_dot(i, n))));
}

//* Schlick's approximation
//* r0 = ((1 - n) / (1 + n))^2
//* R(θ) = r0 + (1 - r0)(1 - cosθ)^5
t_real	reflectance(t_real cosine, t_real n)
{
	t_real	r0;

	r0 = (1.0 - n) / (1.0 + n);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * powf((1.0 - cosine), 5.0));
}

t_bool	vec_refract(t_vec3 uv, t_vec3 n, t_real ni_over_nt, t_vec3 *refracted)
{
	t_real	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_para;
	t_real	discriminant;

	cos_theta = fminf(vec3_dot(vec3_scale(uv, -1.0), n), 1.0);
	r_out_perp = vec3_scale(vec3_add(uv, vec3_scale(n, cos_theta)), ni_over_nt);
	discriminant = 1.0 - vec3_len_squared(r_out_perp);
	if (discriminant > 0.0)
	{
		r_out_para = vec3_scale(n, -sqrtf(discriminant));
		*refracted = vec3_add(r_out_perp, r_out_para);
		return (TRUE);
	}
	return (FALSE);
}

t_color	beer_lambert(t_color color, t_real dist,
		t_color absorbance)
{
	t_color	transmission;

	transmission.r = expf(-absorbance.r * dist);
	transmission.g = expf(-absorbance.g * dist);
	transmission.b = expf(-absorbance.b * dist);
	return (color_prod(color, transmission));
}
