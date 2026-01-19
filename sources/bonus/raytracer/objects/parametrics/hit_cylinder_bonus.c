/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:22 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:28:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	check_tube_root(t_cylinder_hit *hit, t_real t)
{
	t_real	y;

	if (t <= EPSILON || t >= hit->t)
		return ;
	y = hit->ray.origin.y + t * hit->ray.direction.y;
	if (y < -0.5 || y > 0.5)
		return ;
	hit->t = t;
	hit->type = BODY;
}

static void	solve_tube(t_cylinder_hit *hit)
{
	t_vec3		d;
	t_vec3		o;
	t_quadratic	*vars;

	vars = &hit->quadratic_vars;
	d = hit->ray.direction;
	o = hit->ray.origin;
	vars->a = (d.x * d.x) + (d.z * d.z);
	if (fabs(vars->a) < EPSILON)
		return ;
	vars->half_b = (o.x * d.x) + (o.z * d.z);
	vars->c = (o.x * o.x) + (o.z * o.z) - 1.0;
	if (solve_quadratic(vars) == FALSE)
		return ;
	check_tube_root(hit, vars->root1);
	check_tube_root(hit, vars->root2);
}

static void	check_cap(t_cylinder_hit *hit, t_real y_plane,
		t_cylinder_element type)
{
	t_real	t;
	t_real	x;
	t_real	z;
	t_vec3	d;
	t_vec3	o;

	d = hit->ray.direction;
	o = hit->ray.origin;
	if (fabs(d.y) < EPSILON)
		return ;
	t = (y_plane - o.y) / d.y;
	if (t <= EPSILON || t >= hit->t)
		return ;
	x = o.x + (t * d.x);
	z = o.z + (t * d.z);
	if ((x * x) + (z * z) > 1.0)
		return ;
	hit->t = t;
	hit->type = type;
}

static void	set_cylinder_record(t_object *object, t_ray *world_ray,
		t_hit_record *record, t_cylinder_hit *hit)
{
	t_ray	*local_ray;
	t_vec3	local_normal;
	t_vec3	local_hit_point;

	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	local_ray = &hit->ray;
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	if (hit->type == TOP_CAP)
		local_normal = (t_vec3){0, 1, 0};
	else if (hit->type == BOTTOM_CAP)
		local_normal = (t_vec3){0, -1, 0};
	else
	{
		local_hit_point = ray_at(local_ray, record->t);
		local_normal = (t_vec3){local_hit_point.x, 0, local_hit_point.z};
	}
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_cylinder(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_cylinder_hit	hit;
	t_point3		local_hit_point;
	t_point3		world_hit_point;
	t_real			world_dist;

	hit.ray = transform_ray(*world_ray, object->inverse);
	hit.t = INFINITY;
	hit.type = NONE_ELEMENT;
	solve_tube(&hit);
	check_cap(&hit, 0.5, TOP_CAP);
	check_cap(&hit, -0.5, BOTTOM_CAP);
	if (hit.type == NONE_ELEMENT)
		return (FALSE);
	local_hit_point = ray_at(&hit.ray, hit.t);
	world_hit_point = mat4_mult_point3(object->transform, local_hit_point);
	world_dist = vec3_dist(world_ray->origin, world_hit_point);
	if (world_dist < world_ray->min || world_dist > world_ray->max)
		return (FALSE);
	record->t = world_dist;
	set_cylinder_record(object, world_ray, record, &hit);
	return (TRUE);
}
