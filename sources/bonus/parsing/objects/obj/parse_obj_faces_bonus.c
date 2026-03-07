/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_faces_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 18:45:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec3	transform_vertex(t_vec3 v, t_obj_data *data)
{
	t_mat4	rot;
	t_vec3	res;

	res = vec3_scale(v, data->scale);
	rot = rotation_align(data->rotation);
	res = mat4_mult_vec3(rot, res);
	res = vec3_add(res, data->position);
	return (res);
}

static void	init_obj_triangle(t_object *obj, t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	t_triangle	*triangle;
	t_vec3		center;
	t_mat4		transform;

	triangle = &obj->u_data.triangle;
	triangle->p1 = p1;
	triangle->p2 = p2;
	triangle->p3 = p3;
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

static t_status	create_triangle(t_scene *scene, t_obj_data *data, int *idx)
{
	t_object	*obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
	{
		print_error_limit(scene, scene->line_ptr, "objects", MAX_OBJECTS);
		return (EXIT_FAILURE);
	}
	if (idx[0] < 0 || idx[0] >= data->v_count || idx[1] < 0
		|| idx[1] >= data->v_count || idx[2] < 0 || idx[2] >= data->v_count)
	{
		print_error_loc(scene, scene->line_ptr, "Invalid vertex index");
		return (EXIT_FAILURE);
	}
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	obj->type = TRIANGLE;
	obj->color = data->base_color;
	obj->material = data->active_material;
	init_obj_triangle(obj, transform_vertex(data->v_array[idx[0]], data),
		transform_vertex(data->v_array[idx[1]], data),
		transform_vertex(data->v_array[idx[2]], data));
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}

static int	parse_face_indices(char **line, int *v_idx, int max, int total)
{
	int	count;
	int	val;

	count = 0;
	while (**line && **line != '\n' && count < max)
	{
		skip_whitespace(line);
		if (**line == '\0' || **line == '\n')
			break ;
		val = ft_atoi(*line);
		if (val < 0)
			v_idx[count] = total + val;
		else
			v_idx[count] = val - 1;
		count++;
		while (**line && **line != ' ' && **line != '\t')
			(*line)++;
	}
	return (count);
}

t_status	parse_obj_face(t_scene *scene, t_obj_data *data, char **line)
{
	int	v_idx[64];
	int	count;
	int	i;
	int	tri[3];

	count = parse_face_indices(line, v_idx, 64, data->v_count);
	if (count < 3)
	{
		print_error_loc(scene, *line, "Face must have at least 3 vertices");
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < count - 1)
	{
		tri[0] = v_idx[0];
		tri[1] = v_idx[i];
		tri[2] = v_idx[i + 1];
		if (create_triangle(scene, data, tri) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
