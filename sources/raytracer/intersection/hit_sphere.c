/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 08:02:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_sphere_record(t_object *object, t_ray *ray,
		t_hit_record *record)
{
	t_vec3	outward_normal;

	record->hit_point = vec3_add(ray->origin, vec3_scale(ray->direction,
				record->t));
	outward_normal = vec3_sub(record->hit_point, object->u_data.sphere.center);
	outward_normal = vec3_scale(outward_normal, 1.0
			/ object->u_data.sphere.radius);
	set_face_normal(record, ray, outward_normal);
	record->color = object->color;
}

t_bool	hit_sphere(t_object *object, t_ray *ray, t_hit_record *record)
{
	t_sphere	*sphere;
	t_poly		vars;
	t_vec3		oc;

	sphere = &object->u_data.sphere;
	oc = vec3_sub(ray->origin, sphere->center);
	vars.a = 1;
	vars.half_b = vec3_dot(oc, ray->direction);
	vars.c = vec3_len_squared(oc) - (sphere->radius_squared);
	if (solve_quadratic(&vars) == FALSE)
		return (FALSE);
	if (vars.root1 > ray->min && vars.root1 < ray->max)
		record->t = vars.root1;
	else if (vars.root2 > ray->min && vars.root2 < ray->max)
		record->t = vars.root2;
	else
		return (FALSE);
	set_sphere_record(object, ray, record);
	return (TRUE);
}
