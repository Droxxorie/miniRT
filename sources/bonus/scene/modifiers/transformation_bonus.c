/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:19:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 17:35:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	set_transform(t_object *object, t_mat4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse = mat4_inverse(object->transform);
	object->transposed_inverse = mat4_transpose(object->inverse);
	object->sdf_scale = get_min_scale_factor(object->transform);
	if (object->sdf_scale < EPSILON)
		object->sdf_scale = 1.0;
	compute_object_bounds(object);
}

static void	apply_rotation_to_matrix(t_object *object, t_mat4 rotation_matrix)
{
	t_point3	position;
	t_mat4		old_transform;

	position.x = object->transform.m[0][3];
	position.y = object->transform.m[1][3];
	position.z = object->transform.m[2][3];
	old_transform = object->transform;
	old_transform.m[0][3] = 0.0;
	old_transform.m[1][3] = 0.0;
	old_transform.m[2][3] = 0.0;
	object->transform = mat4_mult_mat4(rotation_matrix, old_transform);
	object->transform.m[0][3] = position.x;
	object->transform.m[1][3] = position.y;
	object->transform.m[2][3] = position.z;
	set_transform(object, object->transform);
}

void	dispatch_resize(t_object *object, int mode, int direction)
{
	int					i;
	static t_resize_map	map[] = {
	{SPHERE, resize_sphere},
	{CYLINDER, resize_cylinder},
	{RECTANGLE, resize_rectangle},
	{DISK, resize_disk},
	{TRIANGLE, resize_triangle},
	{TORUS, resize_torus},
	{CONE, resize_cone},
	{BOX, resize_box},
	{NONE, NULL}
	};

	if (!object)
		return ;
	i = 0;
	while (map[i].type != NONE)
	{
		if (map[i].type == object->type)
		{
			map[i].func(object, mode, direction);
			return ;
		}
		i++;
	}
}

void	translate_object(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	if (!object)
		return ;
	translation_matrix = make_translation_matrix(translation);
	object->transform = mat4_mult_mat4(translation_matrix, object->transform);
	set_transform(object, object->transform);
}

void	rotate_object(t_object *object, t_vec3 rotation_axis)
{
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
}
