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

static void	sphere_fold(double *z, double *dr, double in_r, double out_r)
{
	double	r_sq;
	double	temp;

	r_sq = z[0] * z[0] + z[1] * z[1] + z[2] * z[2];
	if (r_sq < in_r * in_r)
	{
		temp = (out_r * out_r) / (in_r * in_r);
		z[0] *= temp;
		z[1] *= temp;
		z[2] *= temp;
		if (dr)
			*dr *= temp;
	}
	else if (r_sq < out_r * out_r)
	{
		temp = (out_r * out_r) / r_sq;
		z[0] *= temp;
		z[1] *= temp;
		z[2] *= temp;
		if (dr)
			*dr *= temp;
	}
}

static void	box_fold(double *z, double fold_scale)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (z[i] > fold_scale)
			z[i] = 2.0 * fold_scale - z[i];
		else if (z[i] < -fold_scale)
			z[i] = -2.0 * fold_scale - z[i];
		i++;
	}
}

static t_color	mandelbox_palette(double min_trap, t_object *object)
{
	return (cosine_palette((t_real)log(min_trap + EPSILON),
			(t_color[4]){object->color, (t_color){0.5f, 0.5f, 0.5f},
		(t_color){2.0f, 2.0f, 2.0f}, (t_color){0.00f, 0.15f, 0.30f}}));
}

t_color	get_mandelbox_color(t_point3 p, t_object *object)
{
	double		z[3];
	double		min_trap;
	int			i;
	double		dist;

	z[0] = (double)p.x;
	z[1] = (double)p.y;
	z[2] = (double)p.z;
	min_trap = 1e20;
	i = -1;
	while (++i < 10)
	{
		box_fold(z, (double)object->u_data.mandelbox.fold_factor);
		sphere_fold(z, NULL, (double)object->u_data.mandelbox.inner_radius,
			(double)object->u_data.mandelbox.outer_radius);
		z[0] = z[0] * (double)object->u_data.mandelbox.fold_factor + p.x;
		z[1] = z[1] * (double)object->u_data.mandelbox.fold_factor + p.y;
		z[2] = z[2] * (double)object->u_data.mandelbox.fold_factor + p.z;
		dist = get_trap_distance((t_vec3){(float)z[0], (float)z[1],
				(float)z[2]}, 2);
		if (dist < min_trap)
			min_trap = dist;
	}
	return (mandelbox_palette(min_trap, object));
}

t_real	sdf_mandelbox(t_point3 p, t_object *object)
{
	double		z[3];
	double		dr;
	int			i;

	if (vec3_len(p) - (object->u_data.mandelbox.size * 2.5f) > 1.0f)
		return (vec3_len(p) - (object->u_data.mandelbox.size * 2.5f));
	z[0] = p.x;
	z[1] = p.y;
	z[2] = p.z;
	dr = 1.0;
	i = -1;
	while (++i < 15)
	{
		box_fold(z, (double)object->u_data.mandelbox.fold_factor);
		sphere_fold(z, &dr, (double)object->u_data.mandelbox.inner_radius,
			(double)object->u_data.mandelbox.outer_radius);
		z[0] = z[0] * (double)object->u_data.mandelbox.slice + p.x;
		z[1] = z[1] * (double)object->u_data.mandelbox.slice + p.y;
		z[2] = z[2] * (double)object->u_data.mandelbox.slice + p.z;
		dr = dr * fabs((double)object->u_data.mandelbox.slice) + 1.0;
	}
	return ((t_real)(sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]) / fabs(dr)));
}
