/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_align_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 19:58:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_mat4	rotation_align(t_vec3 dest)
{
	t_mat4	mat;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	ref_up;

	forward = vec3_normalize(dest);
	if (fabsf(forward.y) > 0.99)
		ref_up = (t_vec3){0.0, 0.0, 1.0};
	else
		ref_up = (t_vec3){0.0, 1.0, 0.0};
	right = vec3_normalize(vec3_cross(forward, ref_up));
	up = vec3_normalize(vec3_cross(right, forward));
	mat = identity_matrix();
	mat.m[0][0] = right.x;
	mat.m[0][1] = forward.x;
	mat.m[0][2] = up.x;
	mat.m[1][0] = right.y;
	mat.m[1][1] = forward.y;
	mat.m[1][2] = up.y;
	mat.m[2][0] = right.z;
	mat.m[2][1] = forward.z;
	mat.m[2][2] = up.z;
	return (mat);
}
