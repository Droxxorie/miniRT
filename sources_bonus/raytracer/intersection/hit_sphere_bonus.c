/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:00:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* N = (P - C) / r
static void	set_sphere_record(t_object *object, t_ray *world_ray,
		t_ray *local_ray, t_hit_record *record)
{
	t_vec3	local_normal;

	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	local_normal = ray_at(local_ray, record->t);
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_sphere(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray		local_ray;
	t_quadratic	vars;

	local_ray = transform_ray(*world_ray, object->inverse);
	vars.a = 1.0;
	vars.half_b = vec3_dot(local_ray.origin, local_ray.direction);
	vars.c = vec3_len_squared(local_ray.origin) - 1.0;
	if (solve_quadratic(&vars) == FALSE)
		return (FALSE);
	if (vars.root1 > world_ray->min && vars.root1 < world_ray->max)
		record->t = vars.root1;
	else if (vars.root2 > world_ray->min && vars.root2 < world_ray->max)
		record->t = vars.root2;
	else
		return (FALSE);
	set_sphere_record(object, world_ray, &local_ray, record);
	return (TRUE);
}
