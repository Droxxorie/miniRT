/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:22 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 19:39:38 by eraad            ###   ########.fr       */
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
	t_vec3		direction;
	t_vec3		origin;
	t_quadratic	*vars;

	vars = &hit->quadratic_vars;
	direction = hit->ray.direction;
	origin = hit->ray.origin;
	vars->a = direction.x * direction.x + direction.z * direction.z;
	vars->half_b = (origin.x * direction.x + origin.z * direction.z);
	vars->c = origin.x * origin.x + origin.z * origin.z - 1.0;
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

	if (fabs(hit->ray.direction.y) < EPSILON)
		return ;
	t = (y_plane - hit->ray.origin.y) / hit->ray.direction.y;
	if (t <= EPSILON || t >= hit->t)
		return ;
	x = hit->ray.origin.x + t * hit->ray.direction.x;
	z = hit->ray.origin.z + t * hit->ray.direction.z;
	if ((x * x + z * z) > 1.0)
		return ;
	hit->t = t;
	hit->type = type;
}

static void	set_cylinder_record(t_object *object, t_ray *ray,
		t_hit_record *record, t_cylinder_hit *hit)
{
	t_cylinder	*cylinder;
	t_vec3		cp;
	t_real		h;
	t_vec3		q;

	record->t = hit->t;
	record->hit_point = ray_at(ray, record->t);
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	cylinder = &object->u_data.cylinder;
	if (hit->type == TOP_CAP)
		record->normal = cylinder->axis;
	else if (hit->type == BOTTOM_CAP)
		record->normal = vec3_scale(cylinder->axis, -1);
	else
	{
		cp = vec3_sub(record->hit_point, cylinder->center);
		h = vec3_dot(cp, cylinder->axis);
		q = vec3_add(cylinder->center, vec3_scale(cylinder->axis, h));
		record->normal = vec3_normalize(vec3_sub(record->hit_point, q));
	}
	set_face_normal(record, ray, record->normal);
}

t_bool	hit_cylinder(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_cylinder_hit	hit;

	hit.ray = transform_ray(*world_ray, object->inverse);
	hit.t = world_ray->max;
	hit.type = NONE_ELEMENT;
	solve_tube(&hit);
	check_cap(&hit, 0.5, TOP_CAP);
	check_cap(&hit, -0.5, BOTTOM_CAP);
	if (hit.type == NONE_ELEMENT || hit.t < world_ray->min
		|| hit.t > world_ray->max)
		return (FALSE);
	set_cylinder_record(object, world_ray, record, &hit);
	return (TRUE);
}
