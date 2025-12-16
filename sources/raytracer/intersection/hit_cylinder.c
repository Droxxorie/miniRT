/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:22 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 09:45:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void set_cylinder_record(t_cylinder *cylinder, t_ray *ray, t_hit_record *record, t_cylinder_vars *vars)
{
	t_vec3	axis_point;
	t_vec3	outward_normal;

	record->hit_point = vec3_add(ray->origin, vec3_scale(ray->direction, record->t));
	axis_point = vec3_add(cylinder->center, vec3_scale(cylinder->axis, vars->projection));
	outward_normal = vec3_sub(record->hit_point, axis_point);
	outward_normal = vec3_scale(outward_normal, 1.0 / cylinder->radius);
	set_face_normal(record, ray, outward_normal);
}

static t_bool	is_valid_height(t_cylinder *cylinder, t_cylinder_vars *vars, t_real t)
{
	vars->projection = (vars->dot_dir_axis * t) + vars->dot_oc_axis;
	if (fabs(vars->projection) <= vars->half_height)
		return (TRUE);
	return (FALSE);
}

static void	get_cylinder_vars(t_cylinder *cylinder, t_ray *ray, t_cylinder_vars *vars)
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
	vars->eq_vars.c = vec3_len_squared(cross_oc_axis) - (cylinder->radius_squared);
	vars->eq_vars.min = ray->min;
	vars->eq_vars.max = ray->max;
	vars->half_height = cylinder->height * 0.5;
}

t_bool	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *record)
{
	t_cylinder_vars	vars;

	get_cylinder_vars(cylinder, ray, &vars);
	if (solve_quadratic(&vars.eq_vars) == FALSE)
		return (FALSE);
	if (is_valid_height(cylinder, &vars, vars.eq_vars.root1))
		record->t = vars.eq_vars.root1;
	else if (is_valid_height(cylinder, &vars, vars.eq_vars.root2))
		record->t = vars.eq_vars.root2;
	else
		return (FALSE);
	set_cylinder_record(cylinder, ray, record, &vars);
	return (TRUE);
}
