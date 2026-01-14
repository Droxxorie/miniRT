/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_menger_sponge_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:55:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:58:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_menger_sponge_values(t_scene *scene, char **line,
		t_object *obj)
{
	if (parse_vec3(scene, line,
			&obj->u_data.menger_sponge.postition) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line,
			&obj->u_data.menger_sponge.normal) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line,
			&obj->u_data.menger_sponge.size) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_menger_sponge(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (!new_object)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = MENGER_SPONGE;
	new_object->render_as_sdf = TRUE;
	new_object->is_fractal = TRUE;
	if (get_menger_sponge_values(scene, line, new_object) == EXIT_FAILURE)
	{
		free(new_object);
		return (EXIT_FAILURE);
	}
	init_fractal_matrix(new_object, new_object->u_data.menger_sponge.postition,
		new_object->u_data.menger_sponge.normal,
		new_object->u_data.menger_sponge.size);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
