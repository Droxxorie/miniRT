/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:49:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 19:07:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	get_plane_value(char **line, t_object *obj)
{
	if (parse_vec3(line, &obj->data.plane.origin) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &obj->data.plane.normal) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &obj->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_plane(t_scene *scene, char **line)
{
	t_object	*new_obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit("objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_MEM_PLANE), EXIT_FAILURE);
	new_obj->type = PLANE;
	if (get_plane_value(line, new_obj) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	if (vec3_len_squared(new_obj->data.plane.normal) == 0)
		return (free(new_obj), print_error(ERR_PARSE_PL_N), EXIT_FAILURE);
	new_obj->data.plane.normal = vec3_normalize(new_obj->data.plane.normal);
	new_obj->data.plane.d = -vec3_dot(new_obj->data.plane.normal,
			new_obj->data.plane.origin);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
