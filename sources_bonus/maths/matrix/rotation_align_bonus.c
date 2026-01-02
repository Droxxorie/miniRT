/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_align_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:40:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_mat4	rotation_align(t_vec3 dest)
{
	t_vec3	axis;
	t_real	angle;
	t_vec3	default_dir;

	default_dir = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(dest.x) < EPSILON && fabs(dest.z) < EPSILON && dest.y > 0)
		return (identity_matrix());
	if (fabs(dest.x) < EPSILON && fabs(dest.z) < EPSILON && dest.y < 0)
		return (rotation_mat_x(PI));
	axis = vec3_cross(default_dir, dest);
	axis = vec3_normalize(axis);
	angle = acos(vec3_dot(default_dir, dest));
	return (matrix_axis_angle(axis, angle));
}
