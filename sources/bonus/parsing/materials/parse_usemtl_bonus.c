/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_usemtl_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:31:40 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 14:32:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_usemtl(t_scene *scene, char **line, t_object *object)
{
	char		*material_name;
	t_material	*material_found;

	if (object->material != NULL)
	{
		print_error_loc(scene, *line, ERR_MTL_OBJ);
		return (EXIT_FAILURE);
	}
	material_name = extract_string(line);
	if (material_name == NULL)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	material_found = find_material(scene->materials, material_name);
	if (!material_found)
	{
		print_error_loc(scene, *line, ERR_MTL_NF);
		free(material_name);
		return (EXIT_FAILURE);
	}
	object->material = material_found;
	free(material_name);
	return (EXIT_SUCCESS);
}
