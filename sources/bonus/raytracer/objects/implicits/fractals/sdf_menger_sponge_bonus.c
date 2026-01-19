/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_menger_sponge_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:50:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 14:59:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	menger_iteration(t_vec3 *p, t_real *scale, t_real scale_factor)
{
	t_real	shift;

	shift = 2.0;
	*p = vec3_abs(*p);
	if (p->x < p->y)
		swap_real(&p->x, &p->y);
	if (p->x < p->z)
		swap_real(&p->x, &p->z);
	if (p->y < p->z)
		swap_real(&p->y, &p->z);
	*scale *= scale_factor;
	*p = vec3_scale(*p, scale_factor);
	*p = vec3_add_scalar(*p, -shift);
	if (p->z < -1.0 * (shift / 2.0))
		p->z += shift;
}

t_color	get_menger_sponge_color(t_point3 p, t_object *object)
{
	t_menger_sponge	*sponge;
	t_real			scale;
	t_real			dist;
	t_real			min_trap;
	int				i;

	sponge = &object->u_data.menger_sponge;
	scale = 1.0;
	min_trap = INFINITY;
	i = 0;
	while (i < 3)
	{
		menger_iteration(&p, &scale, sponge->scale_factor);
		dist = (fabs(p.x) + fabs(p.y)) / scale;
		if (dist < min_trap)
			min_trap = dist;
		i++;
	}
	return (cosine_palette(log(min_trap + EPSILON) * 1.5,
			(t_color[4]){object->color,
			(t_color){0.5, 0.5, 0.5},
		(t_color){1.0, 1.0, 1.0},
		(t_color){0.80, 0.90, 0.30}}));
}

t_real	sdf_menger_sponge(t_point3 p, t_object *object)
{
	t_menger_sponge	*sponge;
	t_real			scale;
	t_real			dist;
	int				i;

	sponge = &object->u_data.menger_sponge;
	if (sponge->scale_factor > 3.0)
	{
		dist = sdf_box(p);
		if (dist > 3.0 / sponge->scale_factor)
			return (dist);
	}
	scale = 1.0;
	i = 0;
	while (i < 4)
	{
		menger_iteration(&p, &scale, sponge->scale_factor);
		i++;
	}
	p = vec3_abs(p);
	p = vec3_add_scalar(p, -1.0);
	dist = vec3_len((t_vec3){fmax(p.x, 0.0), fmax(p.y, 0.0), fmax(p.z, 0.0)})
		+ fmin(fmax(p.x, fmax(p.y, p.z)), 0.0);
	return (dist / scale);
}
