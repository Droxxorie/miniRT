/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_triangle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:08:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:52:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	init_triangle_vars(t_triangle_sdf *vars, t_point3 p,
		t_triangle *triangle)
{
	vars->ba = vec3_sub(triangle->p2, triangle->p1);
	vars->pa = vec3_sub(p, triangle->p1);
	vars->cb = vec3_sub(triangle->p3, triangle->p2);
	vars->pb = vec3_sub(p, triangle->p2);
	vars->ac = vec3_sub(triangle->p1, triangle->p3);
	vars->pc = vec3_sub(p, triangle->p3);
	vars->normal = vec3_cross(vars->ba, vars->ac);
}

static t_real	get_edge_dsitance_sq(t_vec3 edge, t_vec3 point_vec)
{
	t_real	h;
	t_vec3	sub;

	h = vec3_dot(edge, point_vec) / vec3_dot(edge, edge);
	h = ft_clamp(h, 0.0, 1.0);
	sub = vec3_sub(vec3_scale(edge, h), point_vec);
	return (vec3_dot(sub, sub));
}

static int	check_edges(t_triangle_sdf *vars)
{
	t_real	s1;
	t_real	s2;
	t_real	s3;

	s1 = ft_sign(vec3_dot(vec3_cross(vars->ba, vars->normal), vars->pa));
	s2 = ft_sign(vec3_dot(vec3_cross(vars->cb, vars->normal), vars->pb));
	s3 = ft_sign(vec3_dot(vec3_cross(vars->ac, vars->normal), vars->pc));
	return ((s1 + s2 + s3) < 2.0);
}

t_real	sdf_triangle(t_point3 p, t_object *object)
{
	t_triangle_sdf	vars;
	t_real			distance_sq;
	t_real			distance_temp;

	init_triangle_vars(&vars, p, &object->u_data.triangle);
	if (check_edges(&vars))
	{
		distance_sq = get_edge_dsitance_sq(vars.ba, vars.pa);
		distance_temp = get_edge_dsitance_sq(vars.cb, vars.pb);
		distance_sq = fmin(distance_sq, distance_temp);
		distance_temp = get_edge_dsitance_sq(vars.ac, vars.pc);
		distance_sq = fmin(distance_sq, distance_temp);
	}
	else
	{
		distance_sq = vec3_dot(vars.normal, vars.pa);
		distance_sq = distance_sq * distance_sq / vec3_dot(vars.normal,
				vars.normal);
	}
	return (sqrt(distance_sq) - SDF_THICKNESS);
}
