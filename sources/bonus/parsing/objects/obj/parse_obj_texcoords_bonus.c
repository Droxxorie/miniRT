/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_texcoords_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 22:43:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_status	add_texcoord(t_scene *scene, t_obj_data *data, t_vec2 vt)
{
	t_vec2	*new_array;
	int		new_capacity;
	int		i;

	(void)scene;
	if (data->vt_count >= data->vt_capacity)
	{
		if (data->vt_capacity == 0)
			new_capacity = 256;
		else
			new_capacity = data->vt_capacity * 2;
		new_array = malloc(sizeof(t_vec2) * new_capacity);
		if (!new_array)
			return (print_error(ERR_MEM), EXIT_FAILURE);
		i = -1;
		while (++i < data->vt_count)
			new_array[i] = data->vt_array[i];
		free(data->vt_array);
		data->vt_array = new_array;
		data->vt_capacity = new_capacity;
	}
	data->vt_array[data->vt_count++] = vt;
	return (EXIT_SUCCESS);
}

t_status	parse_obj_texcoord(t_scene *scene, t_obj_data *data, char **line)
{
	t_vec2	vt;

	skip_whitespace(line);
	if (parse_real(line, &vt.x) == EXIT_FAILURE)
	{
		print_error_loc(scene, *line, "Invalid texcoord syntax");
		return (EXIT_FAILURE);
	}
	skip_whitespace(line);
	if (parse_real(line, &vt.y) == EXIT_FAILURE)
	{
		print_error_loc(scene, *line, "Invalid texcoord syntax");
		return (EXIT_FAILURE);
	}
	return (add_texcoord(scene, data, vt));
}
