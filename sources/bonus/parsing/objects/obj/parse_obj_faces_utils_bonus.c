/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_faces_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:45:31 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 18:45:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec3	transform_vertex(t_vec3 v, t_obj_data *data)
{
	t_mat4	rot;
	t_vec3	res;

	res = vec3_scale(v, data->scale);
	rot = rotation_align(data->rotation);
	res = mat4_mult_vec3(rot, res);
	res = vec3_add(res, data->position);
	return (res);
}

void	init_obj_triangle(t_object *obj, t_vec3 p[3], t_vec2 uv[3])
{
	t_triangle	*triangle;
	t_vec3		center;
	t_mat4		transform;

	triangle = &obj->u_data.triangle;
	triangle->p1 = p[0];
	triangle->p2 = p[1];
	triangle->p3 = p[2];
	triangle->uv0 = uv[0];
	triangle->uv1 = uv[1];
	triangle->uv2 = uv[2];
	center = vec3_add(triangle->p1, triangle->p2);
	center = vec3_add(center, triangle->p3);
	center = vec3_scale(center, 1.0 / 3.0);
	triangle->p1 = vec3_sub(triangle->p1, center);
	triangle->p2 = vec3_sub(triangle->p2, center);
	triangle->p3 = vec3_sub(triangle->p3, center);
	triangle->edge1 = vec3_sub(triangle->p2, triangle->p1);
	triangle->edge2 = vec3_sub(triangle->p3, triangle->p1);
	triangle->normal = vec3_normalize(vec3_cross(triangle->edge1,
				triangle->edge2));
	transform = make_translation_matrix(center);
	set_transform(obj, transform);
}

t_bool	check_obj_indices(t_obj_data *data, int *v_idx)
{
	if (v_idx[0] < 0 || v_idx[0] >= data->v_count
		|| v_idx[1] < 0 || v_idx[1] >= data->v_count
		|| v_idx[2] < 0 || v_idx[2] >= data->v_count)
		return (FALSE);
	return (TRUE);
}
