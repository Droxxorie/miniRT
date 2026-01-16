/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_mandelbox_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:38:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 14:09:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	sphere_fold(t_vec3 *z, t_real *dr, t_real inner_r, t_real outer_r)
{
	t_real	r_sq;
	t_real	fixed_r_sq;
	t_real	min_r_sq;
	t_real	temp;

	r_sq = vec3_dot(*z, *z);
	fixed_r_sq = outer_r * outer_r;
	min_r_sq = inner_r * inner_r;
	if (r_sq < min_r_sq)
	{
		temp = fixed_r_sq / min_r_sq;
		*z = vec3_scale(*z, temp);
		if (dr)
			*dr *= temp;
	}
	else if (r_sq < fixed_r_sq)
	{
		temp = fixed_r_sq / r_sq;
		*z = vec3_scale(*z, temp);
		if (dr)
			*dr *= temp;
	}
}

static void	box_fold(t_vec3 *z, t_real fold_scale)
{
	if (z->x > fold_scale)
		z->x = 2.0 * fold_scale - z->x;
	else if (z->x < -fold_scale)
		z->x = -2.0 * fold_scale - z->x;
	if (z->y > fold_scale)
		z->y = 2.0 * fold_scale - z->y;
	else if (z->y < -fold_scale)
		z->y = -2.0 * fold_scale - z->y;
	if (z->z > fold_scale)
		z->z = 2.0 * fold_scale - z->z;
	else if (z->z < -fold_scale)
		z->z = -2.0 * fold_scale - z->z;
}

t_color	get_mandelbox_color(t_point3 p, t_object *object)
{
	t_vec3		z;
	t_real		min_trap;
	int			i;
	t_real		dist;
	t_mandelbox	*mandelbox;

	mandelbox = &object->u_data.mandelbox;
	z = p;
	min_trap = 1e20;
	i = 0;
	while (i < 10)
	{
		box_fold(&z, mandelbox->fold_factor);
		sphere_fold(&z, NULL, mandelbox->inner_radius, mandelbox->outer_radius);
		z = vec3_scale(z, mandelbox->fold_factor);
		z = vec3_add(z, p);
		dist = get_trap_distance(z, 2);
		if (dist < min_trap)
			min_trap = dist;
		i++;
	}
	return (cosine_palette(log(min_trap + EPSILON), (t_color[4]){object->color,
			(t_color){0.5, 0.5, 0.5}, (t_color){2.0, 2.0, 2.0}, (t_color){0.00,
			0.15, 0.30}}));
}

t_real	sdf_mandelbox(t_point3 p, t_object *object)
{
	t_vec3		z;
	t_real		dr;
	t_real		dist_bounding_sphere;
	int			i;
	t_mandelbox	*mandelbox;

	mandelbox = &object->u_data.mandelbox;
	dist_bounding_sphere = vec3_len(p) - (mandelbox->size * 2.5);
	if (dist_bounding_sphere > 1.0)
		return (dist_bounding_sphere);
	z = p;
	dr = 1.0;
	i = 0;
	while (i < 15)
	{
		box_fold(&z, mandelbox->fold_factor);
		sphere_fold(&z, &dr, mandelbox->inner_radius, mandelbox->outer_radius);
		z = vec3_scale(z, mandelbox->slice);
		z = vec3_add(z, p);
		dr = dr * fabs(mandelbox->slice) + 1.0;
		i++;
	}
	return (vec3_len(z) / fabs(dr));
}
