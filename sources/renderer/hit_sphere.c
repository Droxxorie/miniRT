/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 22:53:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_sphere_record(t_sphere *sphere, t_ray *ray, t_hit_record *record)
{
	t_vec3	outward_normal;

	record->point = vec3_add(ray->origin, vec3_scale(ray->direction, record->t));
	outward_normal = vec3_sub(record->point, sphere->center);
	outward_normal = vec3_scale(outward_normal, 1.0 / sphere->radius);
	record->front_face = vec3_dot(ray->direction, outward_normal) < 0;
	if (record->front_face)
		record->normal = outward_normal;
	else
		record->normal = vec3_scale(outward_normal, -1.0);
}

t_bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *record)
{
	t_poly	vars;
	t_vec3	oc;
	
	oc = vec3_sub(ray->origin, sphere->center);
	vars.a = vec3_len_squared(ray->direction);
	vars.half_b = vec3_dot(oc, ray->direction);
	vars.c = vec3_len_squared(oc) - (sphere->radius * sphere->radius);
	if (solve_quadratic(&vars) == FALSE)
		return (FALSE);
	if (vars.root1 > ray->min && vars.root1 < ray->max)
		record->t = vars.root1;
	else if (vars.root2 > ray->min && vars.root2 < ray->max)
		record->t = vars.root2;
	else
		return (FALSE);
	set_sphere_record(sphere, ray, record);
	return (TRUE);
}
