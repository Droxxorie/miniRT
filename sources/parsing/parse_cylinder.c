/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:05:08 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 16:44:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	get_cylinder_value(t_scene *scene, char **line, t_object *obj,
		t_real *d)
{
	char	*start_line;

	if (parse_vec3(scene, line, &obj->u_data.cylinder.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line, &obj->u_data.cylinder.axis) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_line = *line;
	if (parse_real(line, d) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_D), EXIT_FAILURE);
	if (*d <= 0)
		return (print_error_loc(scene, start_line, ERR_D_OOR), EXIT_FAILURE);
	if (skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_line = *line;
	if (parse_real(line, &obj->u_data.cylinder.height) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_H), EXIT_FAILURE);
	if (obj->u_data.cylinder.height <= 0)
		return (print_error_loc(scene, start_line, ERR_H_OOR), EXIT_FAILURE);
	if (skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_cylinder(t_scene *scene, char **line)
{
	t_object	*obj;
	t_real		diameter;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	obj = ft_calloc(1, sizeof(t_object));
	if (obj == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	obj->type = CYLINDER;
	if (get_cylinder_value(scene, line, obj, &diameter) == EXIT_FAILURE)
		return (free(obj), EXIT_FAILURE);
	obj->u_data.cylinder.radius = diameter * 0.5;
	obj->u_data.cylinder.radius_squared = obj->u_data.cylinder.radius
		* obj->u_data.cylinder.radius;
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}
