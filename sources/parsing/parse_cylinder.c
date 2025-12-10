/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:05:08 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:18:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status check_vars(t_real diameter, t_real height, t_vec3 axis)
{
	if (diameter <= 0)
	{
		print_error(ERR_PARSE_CYL_D);
		return (EXIT_FAILURE);
	}
	if (height <= 0)
	{
		print_error(ERR_PARSE_CYL_H);
		return (EXIT_FAILURE);
	}
	if (vec3_len_squared(axis) == 0)
	{
		print_error(ERR_PARSE_CYL_A);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_status	parse_cylinder(t_scene *scene, char **line)
{
	t_objects	*object;
	t_real		diameter;

	object = ft_calloc(1, sizeof(t_objects));
	if (object == NULL)
		return (print_error(ERR_CYLINDER_MEM), EXIT_FAILURE);
	object->type = CYLINDER;
	if (parse_vec3(line, &object->data.cylinder.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &object->data.cylinder.axis) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &diameter) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &object->data.cylinder.height) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &object->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(object), EXIT_FAILURE);
	if (check_vars(diameter, object->data.cylinder.height,
			object->data.cylinder.axis) == EXIT_FAILURE)
		return (free(object), EXIT_FAILURE);
	object->data.cylinder.radius = diameter * 0.5;
	object->data.cylinder.axis = vec3_normalize(object->data.cylinder.axis);
	add_object_to_scene(scene, object);
	return (EXIT_SUCCESS);
}
