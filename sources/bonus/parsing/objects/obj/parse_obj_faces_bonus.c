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

static t_object	*alloc_triangle(t_scene *scene, t_obj_data *data, int *v_idx)
{
	t_object	*obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
	{
		print_error_limit(scene, scene->line_ptr, "objects", MAX_OBJECTS);
		return (NULL);
	}
	if (check_obj_indices(data, v_idx) == FALSE)
	{
		print_error_loc(scene, scene->line_ptr, "Invalid vertex");
		return (NULL);
	}
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
	{
		print_error(ERR_MEM_OBJECT);
		return (NULL);
	}
	obj->type = TRIANGLE;
	obj->color = data->base_color;
	obj->material = data->active_material;
	return (obj);
}

static t_status	create_triangle(t_scene *scene, t_obj_data *data, int *v_idx,
		int *vt_idx)
{
	t_object	*obj;
	t_vec3		p[3];
	t_vec2		uv[3];
	int			i;

	obj = alloc_triangle(scene, data, v_idx);
	if (!obj)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < 3)
	{
		p[i] = transform_vertex(data->v_array[v_idx[i]], data);
		uv[i].x = (i == 1);
		uv[i].y = (i == 2);
		if (vt_idx[i] >= 0 && vt_idx[i] < data->vt_count)
			uv[i] = data->vt_array[vt_idx[i]];
	}
	init_obj_triangle(obj, p, uv);
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}

static void	parse_vt_index(char **line, int idx[2][64], int c, t_obj_data *data)
{
	idx[1][c] = ft_atoi(*line) - 1;
	if (idx[1][c] < -1)
		idx[1][c] += data->vt_count + 1;
}

static int	parse_face_indices(char **line, int idx[2][64], t_obj_data *data)
{
	int	c;

	c = 0;
	while (c < 64)
	{
		skip_whitespace(line);
		if (!**line || **line == '\n')
			break ;
		idx[0][c] = ft_atoi(*line) - 1;
		if (idx[0][c] < -1)
			idx[0][c] += data->v_count + 1;
		idx[1][c] = -1;
		while (**line && **line != '/' && **line != ' ' && **line != '\t')
			(*line)++;
		if (**line == '/')
		{
			(*line)++;
			if (**line != '/' && **line != ' ' && **line != '\t')
				parse_vt_index(line, idx, c, data);
		}
		while (**line && **line != ' ' && **line != '\t')
			(*line)++;
		c++;
	}
	return (c);
}

t_status	parse_obj_face(t_scene *scene, t_obj_data *data, char **line)
{
	int	idx[2][64];
	int	count;
	int	i;
	int	tri[2][3];

	count = parse_face_indices(line, idx, data);
	if (count < 3)
	{
		print_error_loc(scene, *line, "Face must have at least 3 vertices");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (++i < count - 1)
	{
		tri[0][0] = idx[0][0];
		tri[0][1] = idx[0][i];
		tri[0][2] = idx[0][i + 1];
		tri[1][0] = idx[1][0];
		tri[1][1] = idx[1][i];
		tri[1][2] = idx[1][i + 1];
		if (create_triangle(scene, data, tri[0], tri[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
