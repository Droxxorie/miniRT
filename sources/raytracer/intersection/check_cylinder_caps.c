/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_caps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:42:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 19:39:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	check_top_cap(t_object *object, t_ray *ray, t_hit_record *record,
		t_cylinder_vars *vars)
{
	t_real		denominator;
	t_real		t;
	t_vec3		p;
	t_cylinder	*cylinder;

	denominator = vars->cap_denom;
	cylinder = &object->u_data.cylinder;
	if (fabs(denominator) < EPSILON)
		return ;
	t = vec3_dot(vec3_sub(vars->top_center, ray->origin),
			cylinder->axis) / denominator;
	if (t < ray->min || t > ray->max || t >= record->t)
		return ;
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	if (vec3_len_squared(vec3_sub(p,
				vars->top_center)) > (cylinder->radius_squared))
		return ;
	record->t = t;
	record->hit_point = p;
	if (record->need_details == FALSE)
		return ;
	set_face_normal(record, ray, object->u_data.cylinder.axis);
	record->color = object->color;
}

static void	check_bottom_cap(t_object *object, t_ray *ray, t_hit_record *record,
		t_cylinder_vars *vars)
{
	t_real		denominator;
	t_real		t;
	t_vec3		p;
	t_cylinder	*cylinder;

	denominator = -vars->cap_denom;
	cylinder = &object->u_data.cylinder;
	if (fabs(denominator) < EPSILON)
		return ;
	t = vec3_dot(vec3_sub(vars->bottom_center, ray->origin),
			vec3_scale(cylinder->axis, -1.0)) / denominator;
	if (t < ray->min || t > ray->max || t >= record->t)
		return ;
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	if (vec3_len_squared(vec3_sub(p,
				vars->bottom_center)) > (cylinder->radius_squared))
		return ;
	record->t = t;
	record->hit_point = p;
	if (record->need_details == FALSE)
		return ;
	set_face_normal(record, ray, vec3_scale(object->u_data.cylinder.axis,
			-1.0));
	record->color = object->color;
}

void	check_cylinder_caps(t_object *object, t_ray *ray, t_hit_record *record,
		t_cylinder_vars *vars)
{
	check_top_cap(object, ray, record, vars);
	check_bottom_cap(object, ray, record, vars);
}
