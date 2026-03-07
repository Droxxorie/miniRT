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

static void	init_obj_triangle(t_object *obj, t_vec3 p[3], t_vec2 uv[3])
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

static t_status	create_triangle(t_scene *scene, t_obj_data *data, int *v_idx,
		int *vt_idx)
{
	t_object	*obj;
	t_vec3		p[3];
	t_vec2		uv[3];

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, scene->line_ptr, "objects",
				MAX_OBJECTS), EXIT_FAILURE);
	if (v_idx[0] < 0 || v_idx[0] >= data->v_count || v_idx[1] < 0
		|| v_idx[1] >= data->v_count || v_idx[2] < 0 || v_idx[2] >= data->v_count)
		return (print_error_loc(scene, scene->line_ptr, "Invalid vertex"), 1);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	obj->type = TRIANGLE;
	obj->color = data->base_color;
	obj->material = data->active_material;
	p[0] = transform_vertex(data->v_array[v_idx[0]], data);
	p[1] = transform_vertex(data->v_array[v_idx[1]], data);
	p[2] = transform_vertex(data->v_array[v_idx[2]], data);
	uv[0] = (t_vec2){0, 0};
	if (vt_idx[0] >= 0 && vt_idx[0] < data->vt_count)
		uv[0] = data->vt_array[vt_idx[0]];
	uv[1] = (t_vec2){1, 0};
	if (vt_idx[1] >= 0 && vt_idx[1] < data->vt_count)
		uv[1] = data->vt_array[vt_idx[1]];
	uv[2] = (t_vec2){0, 1};
	if (vt_idx[2] >= 0 && vt_idx[2] < data->vt_count)
		uv[2] = data->vt_array[vt_idx[2]];
	init_obj_triangle(obj, p, uv);
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}

static int	parse_face_indices(char **line, int *v_idx, int *vt_idx,
		t_obj_data *data)
{
	int	count;
	int	val;

	count = 0;
	while (**line && **line != '\n' && count < 64)
	{
		skip_whitespace(line);
		if (**line == '\0' || **line == '\n')
			break ;
		val = ft_atoi(*line);
		if (val < 0)
			v_idx[count] = data->v_count + val;
		else
			v_idx[count] = val - 1;
		vt_idx[count] = -1;
		while (**line && **line != '/' && **line != ' ' && **line != '\t')
			(*line)++;
		if (**line == '/')
		{
			(*line)++;
			if (**line != '/' && **line != ' ' && **line != '\t')
			{
				val = ft_atoi(*line);
				if (val < 0)
					vt_idx[count] = data->vt_count + val;
				else
					vt_idx[count] = val - 1;
			}
		}
		count++;
		while (**line && **line != ' ' && **line != '\t')
			(*line)++;
	}
	return (count);
}

t_status	parse_obj_face(t_scene *scene, t_obj_data *data, char **line)
{
	int	v_idx[64];
	int	vt_idx[64];
	int	count;
	int	i;
	int	tri_v[3];
	int	tri_vt[3];

	count = parse_face_indices(line, v_idx, vt_idx, data);
	if (count < 3)
	{
		print_error_loc(scene, *line, "Face must have at least 3 vertices");
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < count - 1)
	{
		tri_v[0] = v_idx[0];
		tri_v[1] = v_idx[i];
		tri_v[2] = v_idx[i + 1];
		tri_vt[0] = vt_idx[0];
		tri_vt[1] = vt_idx[i];
		tri_vt[2] = vt_idx[i + 1];
		if (create_triangle(scene, data, tri_v, tri_vt) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
