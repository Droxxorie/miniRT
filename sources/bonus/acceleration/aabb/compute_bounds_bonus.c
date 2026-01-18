/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_bounds_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:37:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/17 13:38:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

static void	compute_more_bounds(t_object *object, t_aabb *local_box)
{
	if (object->type == TORUS)
		*local_box = compute_torus_bounds(object);
	else if (object->type == MENGER_SPONGE)
		*local_box = compute_menger_sponge_bounds();
	else if (object->type == MANDELBULB)
		*local_box = compute_mandelbulb_bounds();
	else if (object->type == MANDELBOX)
		*local_box = compute_mandelbox_bounds();
	else if (object->type == JULIA_SET)
		*local_box = compute_julia_set_bounds();
}

void	compute_object_bounds(t_object *object)
{
	t_aabb	local_box;

	if (object->type == BOX)
		local_box = compute_box_bounds();
	else if (object->type == RECTANGLE)
		local_box = compute_rectangle_bounds();
	else if (object->type == DISK)
		local_box = compute_disk_bounds();
	else if (object->type == SPHERE)
		local_box = compute_sphere_bounds();
	else if (object->type == CYLINDER)
		local_box = compute_cylinder_bounds();
	else if (object->type == CONE)
		local_box = compute_cone_bounds();
	else if (object->type == TRIANGLE)
	{
		object->aabb = compute_triangle_bounds(object);
		return ;
	}
	else
		compute_more_bounds(object, &local_box);
	local_box.min = vec3_add_scalar(local_box.min, -BVH_PADDING);
	local_box.max = vec3_add_scalar(local_box.max, BVH_PADDING);
	object->aabb = transform_aabb(local_box, object->transform);
}
