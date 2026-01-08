/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_triangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:06:43 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 22:11:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_triangle_matrix(t_object *object)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	normal;
	t_mat4	matrix;

	u = vec3_sub(object->u_data.triangle.p2, object->u_data.triangle.p1);
	v = vec3_sub(object->u_data.triangle.p3, object->u_data.triangle.p1);
	normal = vec3_normalize(vec3_cross(u, v));
	matrix.m[0][0] = u.x;
	matrix.m[1][0] = u.y;
	matrix.m[2][0] = u.z;
	matrix.m[3][0] = 0.0;
	matrix.m[0][1] = v.x;
	matrix.m[1][1] = v.y;
	matrix.m[2][1] = v.z;
	matrix.m[3][1] = 0.0;
	matrix.m[0][2] = normal.x;
	matrix.m[1][2] = normal.y;
	matrix.m[2][2] = normal.z;
	matrix.m[3][2] = 0.0;
	matrix.m[0][3] = object->u_data.triangle.p1.x;
	matrix.m[1][3] = object->u_data.triangle.p1.y;
	matrix.m[2][3] = object->u_data.triangle.p1.z;
	matrix.m[3][3] = 1.0;
	set_transform(object, matrix);
}
