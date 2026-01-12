/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_bounds_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:37:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 13:03:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	empty_aabb(void)
{
	t_aabb	box;

	box.min = (t_point3){INFINITY, INFINITY, INFINITY};
	box.max = (t_point3){-INFINITY, -INFINITY, -INFINITY};
	return (box);
}

void	grow_aabb(t_aabb *box, t_point3 point)
{
	box->min.x = fmin(box->min.x, point.x);
	box->min.y = fmin(box->min.y, point.y);
	box->min.z = fmin(box->min.z, point.z);
	box->max.x = fmax(box->max.x, point.x);
	box->max.y = fmax(box->max.y, point.y);
	box->max.z = fmax(box->max.z, point.z);
}

t_aabb	surrounding_box(t_aabb box1, t_aabb box2)
{
	t_aabb	surround_box;

	surround_box.min.x = fmin(box1.min.x, box2.min.x);
	surround_box.min.y = fmin(box1.min.y, box2.min.y);
	surround_box.min.z = fmin(box1.min.z, box2.min.z);
	surround_box.max.x = fmax(box1.max.x, box2.max.x);
	surround_box.max.y = fmax(box1.max.y, box2.max.y);
	surround_box.max.z = fmax(box1.max.z, box2.max.z);
	return (surround_box);
}

static t_aabb	transform_aabb(t_aabb local_box, t_mat4 transform)
{
	t_aabb		world_box;
	t_point3	corner;
	int			i;

	world_box = empty_aabb();
	i = -1;
	while (++i < 8)
	{
		if (i & 1)
			corner.x = local_box.min.x;
		else
			corner.x = local_box.max.x;
		if (i & 2)
			corner.y = local_box.min.y;
		else
			corner.y = local_box.max.y;
		if (i & 4)
			corner.z = local_box.min.z;
		else
			corner.z = local_box.max.z;
		corner = mat4_mult_point3(transform, corner);
		grow_aabb(&world_box, corner);
	}
	return (world_box);
}

void	compute_object_bounds(t_object *object)
{
	t_aabb		local_box;

	if (object->type == BOX)
		local_box = compute_box_bounds();
	if (object->type == RECTANGLE)
		local_box = compute_rectangle_bounds();
	if (object->type == DISK)
		local_box = compute_disk_bounds();
	if (object->type == PLANE)
		local_box = compute_plane_bounds();
	if (object->type == SPHERE)
		local_box = compute_sphere_bounds();
	if (object->type == TORUS)
		local_box = compute_torus_bounds(object);
	if (object->type == CYLINDER)
		local_box = compute_cylinder_bounds();
	if (object->type == CONE)
		local_box = compute_cone_bounds();
	if (object->type == TRIANGLE)
	{
		object->aabb = compute_triangle_bounds(object);
		return ;
	}
	object->aabb = transform_aabb(local_box, object->transform);
}
