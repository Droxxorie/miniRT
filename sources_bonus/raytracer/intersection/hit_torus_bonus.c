/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_torus_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:51:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 01:05:47 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	setup_torus_coeffs(t_quartic *vars, t_ray *ray, t_torus *torus)
{
	t_real	dist_sq;
	t_real	od;
	t_real	k;
	t_real	dx_dz_sq;
	t_real	ox_oz_sq;

	dist_sq = vec3_len_squared(ray->direction);
	od = vec3_dot(ray->origin, ray->direction);
	k = vec3_len_squared(ray->origin) + torus->diff_radius_sq;
	dx_dz_sq = (ray->direction.x * ray->direction.x) + (ray->direction.z
			* ray->direction.z);
	ox_oz_sq = (ray->origin.x * ray->origin.x) + (ray->origin.z
			* ray->origin.z);
	vars->coeffs[4] = dist_sq * dist_sq;
	vars->coeffs[3] = 4.0 * dist_sq * od;
	vars->coeffs[2] = 2.0 * dist_sq * k + 4.0 * od * od - 4.0
		* torus->major_radius_sq * dx_dz_sq;
	vars->coeffs[1] = 4.0 * k * od - 8.0 * torus->major_radius_sq
		* (ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z);
	vars->coeffs[0] = k * k - 4.0 * torus->major_radius_sq * ox_oz_sq;
}

static t_bool	find_nearest_root(t_quartic *vars, t_ray *ray, t_real *t)
{
	int		i;
	t_real	t_min;
	t_bool	hit;

	t_min = ray->max;
	hit = FALSE;
	i = 0;
	while (i < vars->roots_count)
	{
		if (vars->roots[i] > ray->min && vars->roots[i] < t_min)
		{
			t_min = vars->roots[i];
			hit = TRUE;
		}
		i++;
	}
	if (hit == TRUE)
		*t = t_min;
	return (hit);
}

//* Gradient
//* Nx = 4x(P^2 + R^2 - r^2) - 8R^2x
//* Ny = 4y(P^2 + R^2 - r^2)
//* Nz = 4z(P^2 + R^2 - r^2) - 8R^2z
static void	get_torus_normal(t_object *object, t_hit_record *record, t_point3 p)
{
	t_torus	*torus;
	t_real	p_sq;
	t_real	factor;
	t_vec3	local_normal;

	torus = &object->u_data.torus;
	p_sq = vec3_len_squared(p);
	factor = p_sq + torus->diff_radius_sq;
	local_normal.x = 4.0 * p.x * factor - 8 * torus->major_radius_sq * p.x;
	local_normal.y = 4.0 * p.y * factor;
	local_normal.z = 4.0 * p.z * factor - 8 * torus->major_radius_sq * p.z;
	record->normal = vec3_normalize(mat4_mult_vec3(object->transposed_inverse,
				local_normal));
}

static void	set_torus_record(t_object *object, t_ray *world_ray,
		t_ray *local_ray, t_hit_record *record)
{
	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	get_torus_normal(object, record, ray_at(local_ray, record->t));
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_torus(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray		local_ray;
	t_torus		*torus;
	t_quartic	vars;

	torus = &object->u_data.torus;
	local_ray = transform_ray(*world_ray, object->inverse);
	setup_torus_coeffs(&vars, &local_ray, torus);
	if (solve_quartic(&vars) == FALSE)
		return (FALSE);
	if (find_nearest_root(&vars, world_ray, &record->t) == FALSE)
		return (FALSE);
	set_torus_record(object, world_ray, &local_ray, record);
	return (TRUE);
}
