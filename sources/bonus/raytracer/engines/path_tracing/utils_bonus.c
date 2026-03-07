/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:03:16 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 16:37:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	build_onb(t_vec3 n, t_vec3 *t, t_vec3 *b)
{
	if (fabsf(n.x) > 0.9)
		*t = (t_vec3){0.0, 1.0, 0.0};
	else
		*t = (t_vec3){1.0, 0.0, 0.0};
	*b = vec3_normalize(vec3_cross(n, *t));
	*t = vec3_cross(*b, n);
}

t_real	power_heuristic(t_real pdf_a, t_real pdf_b)
{
	t_real	f_a;
	t_real	f_b;

	f_a = pdf_a * pdf_a;
	f_b = pdf_b * pdf_b;
	return (f_a / (f_a + f_b + EPSILON));
}

t_bool	is_color_finite(t_color *c)
{
	if (c->r != c->r || c->g != c->g || c->b != c->b)
		return (FALSE);
	if (c->r < -1e6 || c->r > 1e10 || c->g < -1e6 || c->g > 1e10)
		return (FALSE);
	if (c->b < -1e6 || c->b > 1e10)
		return (FALSE);
	return (TRUE);
}

t_bool	russian_roulette(t_path_info *info, t_real p)
{
	t_real	survival_prob;

	if (info->pdf < EPSILON)
		return (TRUE);
	if (info->depth > ROULETTE_START_DEPTH && p < 0.1)
	{
		survival_prob = p;
		if (survival_prob < 0.05)
			survival_prob = 0.05;
		if (random_double(&info->seed) > survival_prob)
			return (TRUE);
		if (survival_prob >= EPSILON)
			info->thru = color_div(info->thru, survival_prob);
	}
	return (FALSE);
}

t_ray	update_ray(t_hit_record *rec, t_vec3 next_dir)
{
	t_vec3	offset;
	t_vec3	origin;

	offset = vec3_scale(rec->normal, 0.01);
	if (vec3_dot(next_dir, rec->normal) > 0.0)
		origin = vec3_add(rec->hit_point, offset);
	else
		origin = vec3_sub(rec->hit_point, offset);
	return (new_ray(origin, next_dir));
}
