/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:05:08 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:56:41 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	radius_helper(t_cylinder *cylinder, t_real diameter)
{
	cylinder->radius = diameter * 0.5;
	cylinder->radius_squared = cylinder->radius * cylinder->radius;
}

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

static t_status	get_cylinder_value(char **line, t_object *obj, t_real *d)
{
	if (parse_vec3(line, &obj->u_data.cylinder.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &obj->u_data.cylinder.axis) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, d) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &obj->u_data.cylinder.height) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &obj->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_cylinder(t_scene *scene, char **line)
{
	t_object	*obj;
	t_real		diameter;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit("objects", MAX_OBJECTS),
			EXIT_FAILURE);
	obj = ft_calloc(1, sizeof(t_object));
	if (obj == NULL)
		return (print_error(ERR_MEM_CYLINDER), EXIT_FAILURE);
	obj->type = CYLINDER;
	if (get_cylinder_value(line, obj, &diameter) == EXIT_FAILURE)
		return (free(obj), EXIT_FAILURE);
	if (check_vars(diameter, obj->u_data.cylinder.height,
			obj->u_data.cylinder.axis) == EXIT_FAILURE)
		return (free(obj), EXIT_FAILURE);
	obj->u_data.cylinder.axis = vec3_normalize(obj->u_data.cylinder.axis);
	radius_helper(&obj->u_data.cylinder, diameter);
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}
