/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_bounds_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:40:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 20:59:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_triangle_bounds(t_object *object)
{
	t_aabb		box;
	t_triangle	*triangle;
	t_point3	p1;
	t_point3	p2;
	t_point3	p3;

	triangle = &object->u_data.triangle;
	p1 = mat4_mult_point3(object->transform, triangle->p1);
	p2 = mat4_mult_point3(object->transform, triangle->p2);
	p3 = mat4_mult_point3(object->transform, triangle->p3);
	box = empty_aabb();
	grow_aabb(&box, p1);
	grow_aabb(&box, p2);
	grow_aabb(&box, p3);
	box.min = vec3_add_scalar(box.min, -EPSILON);
	box.max = vec3_add_scalar(box.max, EPSILON);
	return (box);
}
