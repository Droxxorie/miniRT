/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_vertices_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 18:45:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_status	add_vertex(t_scene *scene, t_obj_data *data, t_vec3 v)
{
	t_vec3	*new_array;
	int		new_capacity;
	int		i;

	(void)scene;
	if (data->v_count >= data->v_capacity)
	{
		if (data->v_capacity == 0)
			new_capacity = 256;
		else
			new_capacity = data->v_capacity * 2;
		new_array = malloc(sizeof(t_vec3) * new_capacity);
		if (!new_array)
			return (print_error(ERR_MEM), EXIT_FAILURE);
		i = -1;
		while (++i < data->v_count)
			new_array[i] = data->v_array[i];
		free(data->v_array);
		data->v_array = new_array;
		data->v_capacity = new_capacity;
	}
	data->v_array[data->v_count++] = v;
	return (EXIT_SUCCESS);
}

static t_status	add_normal(t_scene *scene, t_obj_data *data, t_vec3 vn)
{
	t_vec3	*new_array;
	int		new_capacity;
	int		i;

	(void)scene;
	if (data->vn_count >= data->vn_capacity)
	{
		if (data->vn_capacity == 0)
			new_capacity = 256;
		else
			new_capacity = data->vn_capacity * 2;
		new_array = malloc(sizeof(t_vec3) * new_capacity);
		if (!new_array)
			return (print_error(ERR_MEM), EXIT_FAILURE);
		i = -1;
		while (++i < data->vn_count)
			new_array[i] = data->vn_array[i];
		free(data->vn_array);
		data->vn_array = new_array;
		data->vn_capacity = new_capacity;
	}
	data->vn_array[data->vn_count++] = vn;
	return (EXIT_SUCCESS);
}

static t_status	parse_obj_vec3(char **line, t_vec3 *v)
{
	skip_whitespace(line);
	if (parse_real(line, &v->x) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	skip_whitespace(line);
	if (parse_real(line, &v->y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	skip_whitespace(line);
	if (parse_real(line, &v->z) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_obj_vertex(t_scene *scene, t_obj_data *data, char **line)
{
	t_vec3	v;

	if (parse_obj_vec3(line, &v) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
	{
		print_error_loc(scene, *line, "Invalid vertex syntax");
		return (EXIT_FAILURE);
	}
	return (add_vertex(scene, data, v));
}

t_status	parse_obj_normal(t_scene *scene, t_obj_data *data, char **line)
{
	t_vec3	vn;

	if (parse_obj_vec3(line, &vn) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
	{
		print_error_loc(scene, *line, "Invalid normal syntax");
		return (EXIT_FAILURE);
	}
	vn = vec3_normalize(vn);
	return (add_normal(scene, data, vn));
}
