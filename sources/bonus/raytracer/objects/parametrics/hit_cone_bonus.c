/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:26:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 21:18:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	solve_cone_base(t_cone_hit *hit)
{
	t_real	t;
	t_real	x;
	t_real	z;

	if (fabsf(hit->ray.direction.y) < EPSILON)
		return ;
	t = -hit->ray.origin.y / hit->ray.direction.y;
	if (t <= EPSILON || t >= hit->t)
		return ;
	x = hit->ray.origin.x + (t * hit->ray.direction.x);
	z = hit->ray.origin.z + (t * hit->ray.direction.z);
	if ((x * x) + (z * z) > 1.0)
		return ;
	hit->t = t;
	hit->type = BOTTOM_CAP;
}

static void	check_cone_height(t_cone_hit *hit, t_real t)
{
	t_real	y;

	if (t <= EPSILON || t >= hit->t)
		return ;
	y = hit->ray.origin.y + (t * hit->ray.direction.y);
	if (y < 0.0 || y > 1.0)
		return ;
	hit->t = t;
	hit->type = BODY;
}

static void	solve_cone_body(t_cone_hit *hit)
{
	t_vec3		d;
	t_vec3		o;
	t_quadratic	*vars;
	t_real		k;

	vars = &hit->quadratic_vars;
	d = hit->ray.direction;
	o = hit->ray.origin;
	k = 1.0 - o.y;
	vars->a = d.x * d.x + d.z * d.z - d.y * d.y;
	vars->half_b = o.x * d.x + o.z * d.z + d.y * k;
	vars->c = o.x * o.x + o.z * o.z - k * k;
	if (solve_quadratic(vars) == FALSE)
		return ;
	check_cone_height(hit, vars->root1);
	check_cone_height(hit, vars->root2);
}

static void	set_cone_record(t_object *object, t_ray *world_ray,
		t_hit_record *record, t_cone_hit *hit)
{
	t_ray		*local_ray;
	t_vec3		local_normal;
	t_point3	local_hp;

	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	local_ray = &hit->ray;
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	local_hp = ray_at(local_ray, hit->t);
	get_cone_uv(local_hp, hit->type, &record->u, &record->v);
	if (hit->type == BOTTOM_CAP)
		local_normal = (t_vec3){0, -1, 0};
	else
		local_normal = (t_vec3){local_hp.x, sqrtf((local_hp.x * local_hp.x)
				+ (local_hp.z * local_hp.z)), local_hp.z};
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_cone(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_cone_hit	hit;

	hit.ray = transform_ray(*world_ray, object->inverse);
	hit.t = world_ray->max;
	hit.type = NONE_ELEMENT;
	solve_cone_body(&hit);
	solve_cone_base(&hit);
	if (hit.type == NONE_ELEMENT || hit.t < world_ray->min)
		return (FALSE);
	record->t = hit.t;
	set_cone_record(object, world_ray, record, &hit);
	return (TRUE);
}
