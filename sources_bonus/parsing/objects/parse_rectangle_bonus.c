/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rectangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:34:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:20:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_rectangle_values(t_scene *scene, char **line,
		t_object *object)
{
	if (parse_vec3(scene, line,
			&object->u_data.rectangle.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line,
			&object->u_data.rectangle.normal) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &object->u_data.rectangle.width) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &object->u_data.rectangle.height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &object->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_rectangle(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (new_object == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = RECTANGLE;
	if (get_rectangle_values(scene, line, new_object) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	update_object(new_object);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
