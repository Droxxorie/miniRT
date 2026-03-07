/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_materials_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 18:45:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_status	parse_obj_mtllib(t_scene *scene, t_obj_data *data, char **line)
{
	(void)data;
	return (parse_mtl_lib(scene, line));
}

t_status	parse_obj_usemtl(t_scene *scene, t_obj_data *data, char **line)
{
	char		*mat_name;
	t_material	*mat;

	mat_name = extract_string(line);
	if (!mat_name)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	mat = find_material(scene->materials, mat_name);
	if (!mat)
	{
		print_error_loc(scene, scene->line_ptr, "Material not found");
		free(mat_name);
		return (EXIT_FAILURE);
	}
	data->active_material = mat;
	free(mat_name);
	return (EXIT_SUCCESS);
}
