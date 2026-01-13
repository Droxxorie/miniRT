/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_torus_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:51:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 10:29:07 by eraad            ###   ########.fr       */
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
	vars->coeffs[2] = (2.0 * dist_sq * k) + (4.0 * od * od) - (4.0
			* torus->major_radius_sq * dx_dz_sq);
	vars->coeffs[1] = (4.0 * k * od) - 8.0 * torus->major_radius_sq
		* (ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z);
	vars->coeffs[0] = (k * k) - (4.0 * torus->major_radius_sq * ox_oz_sq);
}

static t_real	find_nearest_root(t_quartic *vars, t_ray *ray, t_real *t,
		t_real scale)
{
	int		i;
	t_real	t_local;
	t_real	t_world;

	*t = ray->max;
	t_local = -1.0;
	i = 0;
	while (i < vars->roots_count)
	{
		t_world = vars->roots[i] / scale;
		if (t_world > ray->min && t_world < *t)
		{
			*t = t_world;
			t_local = vars->roots[i];
		}
		i++;
	}
	return (t_local);
}

//* Gradient
//* Nx = 4x(P^2 + R^2 - r^2) - 8R^2x
//* Ny = 4y(P^2 + R^2 - r^2)
//* Nz = 4z(P^2 + R^2 - r^2) - 8R^2z
static void	get_torus_normal(t_object *object, t_hit_record *record, t_point3 p)
{
	t_torus	*torus;
	t_real	p_sq;
	t_real	k;
	t_vec3	local_normal;

	torus = &object->u_data.torus;
	p_sq = vec3_len_squared(p);
	k = p_sq + torus->diff_radius_sq;
	local_normal.x = (4.0 * p.x * k) - (8.0 * torus->major_radius_sq * p.x);
	local_normal.y = 4.0 * p.y * k;
	local_normal.z = (4.0 * p.z * k) - (8.0 * torus->major_radius_sq * p.z);
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
}

static void	set_torus_record(t_object *object, t_ray *world_ray,
		t_point3 local_hit_point, t_hit_record *record)
{
	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	get_torus_normal(object, record, local_hit_point);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_torus(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray		local_ray;
	t_torus		*torus;
	t_quartic	vars;
	t_real		scale;
	t_real		t_local;

	torus = &object->u_data.torus;
	local_ray = transform_ray(*world_ray, object->inverse);
	scale = vec3_len(local_ray.direction);
	if (scale < EPSILON)
		return (FALSE);
	local_ray.direction = vec3_scale(local_ray.direction, 1.0 / scale);
	setup_torus_coeffs(&vars, &local_ray, torus);
	if (solve_quartic(&vars) == FALSE)
		return (FALSE);
	t_local = find_nearest_root(&vars, &local_ray, &record->t, scale);
	if (t_local < 0.0)
		return (FALSE);
	set_torus_record(object, world_ray, ray_at(&local_ray, t_local), record);
	return (TRUE);
}
