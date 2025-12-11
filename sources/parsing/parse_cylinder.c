/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:05:08 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:29:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	check_vars(t_real diameter, t_real height, t_vec3 axis)
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
	t_object	*new_obj;
	t_real		diameter;

	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_CYLINDER_MEM), EXIT_FAILURE);
	new_obj->type = CYLINDER;
	if (parse_vec3(line, &new_obj->data.cylinder.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &new_obj->data.cylinder.axis) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &diameter) == EXIT_FAILURE || skip_required(line,
			WHITESPACE_CHARS) == EXIT_FAILURE || parse_real(line,
			&new_obj->data.cylinder.height) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &new_obj->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	if (check_vars(diameter, new_obj->data.cylinder.height,
			new_obj->data.cylinder.axis) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	new_obj->data.cylinder.radius = diameter * 0.5;
	new_obj->data.cylinder.axis = vec3_normalize(new_obj->data.cylinder.axis);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
