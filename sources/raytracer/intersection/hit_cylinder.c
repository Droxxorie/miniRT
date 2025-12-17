/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:22 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 19:16:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_cylinder_record(t_object *object, t_ray *ray,
		t_hit_record *record, t_cylinder_vars *vars)
{
	t_vec3	axis_point;
	t_vec3	outward_normal;

	record->hit_point = vec3_add(ray->origin, vec3_scale(ray->direction,
				record->t));
	if (record->need_details == FALSE)
		return ;
	axis_point = vec3_add(object->u_data.cylinder.center,
			vec3_scale(object->u_data.cylinder.axis, vars->projection));
	outward_normal = vec3_sub(record->hit_point, axis_point);
	outward_normal = vec3_scale(outward_normal, 1.0
			/ object->u_data.cylinder.radius);
	set_face_normal(record, ray, outward_normal);
	record->color = object->color;
	record->object = object;
}

static t_bool	is_valid_intersection(t_cylinder_vars *vars, t_ray *ray,
		t_real t)
{
	if (t < ray->min || t > ray->max)
		return (FALSE);
	vars->projection = (vars->dot_dir_axis * t) + vars->dot_oc_axis;
	if (fabs(vars->projection) <= vars->half_height)
		return (TRUE);
	return (FALSE);
}

static void	get_cylinder_vars(t_cylinder *cylinder, t_ray *ray,
		t_cylinder_vars *vars)
{
	t_vec3	cross_dir_axis;
	t_vec3	cross_oc_axis;

	vars->oc = vec3_sub(ray->origin, cylinder->center);
	vars->dot_dir_axis = vec3_dot(ray->direction, cylinder->axis);
	vars->dot_oc_axis = vec3_dot(vars->oc, cylinder->axis);
	cross_dir_axis = vec3_cross(ray->direction, cylinder->axis);
	cross_oc_axis = vec3_cross(vars->oc, cylinder->axis);
	vars->eq_vars.a = vec3_len_squared(cross_dir_axis);
	vars->eq_vars.half_b = vec3_dot(cross_dir_axis, cross_oc_axis);
	vars->eq_vars.c = vec3_len_squared(cross_oc_axis)
		- (cylinder->radius_squared);
	vars->eq_vars.min = ray->min;
	vars->eq_vars.max = ray->max;
	vars->half_height = cylinder->height * 0.5;
	vars->top_center = vec3_add(cylinder->center, vec3_scale(cylinder->axis,
				vars->half_height));
	vars->bottom_center = vec3_sub(cylinder->center, vec3_scale(cylinder->axis,
				vars->half_height));
	vars->cap_denom = vec3_dot(ray->direction, cylinder->axis);
}

t_bool	hit_cylinder(t_object *object, t_ray *ray, t_hit_record *record)
{
	t_cylinder_vars	vars;
	t_bool			hit;

	get_cylinder_vars(&object->u_data.cylinder, ray, &vars);
	hit = FALSE;
	if (solve_quadratic(&vars.eq_vars) == TRUE)
	{
		if (is_valid_intersection(&vars, ray, vars.eq_vars.root1))
		{
			record->t = vars.eq_vars.root1;
			hit = TRUE;
		}
		else if (is_valid_intersection(&vars, ray, vars.eq_vars.root2))
		{
			record->t = vars.eq_vars.root2;
			hit = TRUE;
		}
	}
	if (hit == TRUE)
		set_cylinder_record(object, ray, record, &vars);
	else
		record->t = ray->max;
	check_cylinder_caps(object, ray, record, &vars);
	return (record->t < ray->max);
}
