/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:39:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:42:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	menger_sort(double *p)
{
	double	tmp;

	if (p[0] < p[1])
	{
		tmp = p[0];
		p[0] = p[1];
		p[1] = tmp;
	}
	if (p[0] < p[2])
	{
		tmp = p[0];
		p[0] = p[2];
		p[2] = tmp;
	}
	if (p[1] < p[2])
	{
		tmp = p[1];
		p[1] = p[2];
		p[2] = tmp;
	}
}

static void	menger_iteration(double *p, double *scale, double sf)
{
	p[0] = fabs(p[0]);
	p[1] = fabs(p[1]);
	p[2] = fabs(p[2]);
	menger_sort(p);
	*scale *= sf;
	p[0] = p[0] * sf - 2.0;
	p[1] = p[1] * sf - 2.0;
	p[2] = p[2] * sf - 2.0;
	if (p[2] < -1.0)
		p[2] += 2.0;
}

t_color	get_menger_sponge_color(t_point3 p_in, t_object *object)
{
	double	scale;
	double	dist;
	double	min_trap;
	double	p[3];
	int		i;

	p[0] = (double)p_in.x;
	p[1] = (double)p_in.y;
	p[2] = (double)p_in.z;
	scale = 1.0;
	min_trap = INFINITY;
	i = -1;
	while (++i < 3)
	{
		menger_iteration(p, &scale,
			(double)object->u_data.menger_sponge.scale_factor);
		dist = (fabs(p[0]) + fabs(p[1])) / scale;
		if (dist < min_trap)
			min_trap = dist;
	}
	return (cosine_palette((t_real)(log(min_trap + EPSILON) * 1.5),
		(t_color[4]){object->color, (t_color){0.5f, 0.5f, 0.5f},
		(t_color){1.0f, 1.0f, 1.0f}, (t_color){0.80f, 0.90f, 0.30f}}));
}

static t_real	get_fdist(double *p, double scale)
{
	double	m[3];

	p[0] = fabs(p[0]) - 1.0;
	p[1] = fabs(p[1]) - 1.0;
	p[2] = fabs(p[2]) - 1.0;
	m[0] = fmax(p[0], 0.0);
	m[1] = fmax(p[1], 0.0);
	m[2] = fmax(p[2], 0.0);
	return ((t_real)((sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2])
			+ fmin(fmax(p[0], fmax(p[1], p[2])), 0.0)) / scale));
}

t_real	sdf_menger_sponge(t_point3 p_in, t_object *object)
{
	double	scale;
	double	p[3];
	int		i;

	if (object->u_data.menger_sponge.scale_factor > 3.0f)
	{
		if (sdf_box(p_in) > 3.0f / object->u_data.menger_sponge.scale_factor)
			return (sdf_box(p_in));
	}
	p[0] = (double)p_in.x;
	p[1] = (double)p_in.y;
	p[2] = (double)p_in.z;
	scale = 1.0;
	i = -1;
	while (++i < 4)
	{
		menger_iteration(p, &scale,
			(double)object->u_data.menger_sponge.scale_factor);
	}
	return (get_fdist(p, scale));
}
