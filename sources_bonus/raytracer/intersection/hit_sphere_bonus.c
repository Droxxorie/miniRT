/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 14:23:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* N = (P - C) / r
static void	set_sphere_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	t_sphere	*sphere;

	sphere = &object->u_data.sphere;
	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	record->normal = vec3_scale(vec3_sub(record->hit_point, sphere->center),
			sphere->inv_radius);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_sphere(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_sphere	*sphere;
	t_vec3		oc;
	t_poly		vars;

	sphere = &object->u_data.sphere;
	oc = vec3_sub(world_ray->origin, sphere->center);
	vars.a = 1.0;
	vars.half_b = vec3_dot(oc, world_ray->direction);
	vars.c = vec3_len_squared(oc) - sphere->sq_radius;
	if (solve_quadratic(&vars) == FALSE)
		return (FALSE);
	if (vars.root1 > world_ray->min && vars.root1 < world_ray->max)
		record->t = vars.root1;
	else if (vars.root2 > world_ray->min && vars.root2 < world_ray->max)
		record->t = vars.root2;
	else
		return (FALSE);
	set_sphere_record(object, world_ray, record);
	return (TRUE);
}
