/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:57:59 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 11:46:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	get_sphere_value(t_scene *scene, char **line, t_object *obj,
		t_real *d)
{
	char	*start_line;

	if (parse_vec3(scene, line, &obj->u_data.sphere.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_line = *line;
	if (parse_real(line, d) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_D), EXIT_FAILURE);
	if (*d <= 0)
		return (print_error_loc(scene, start_line, ERR_D_OOR), EXIT_FAILURE);
	if (skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_sphere(t_scene *scene, char **line)
{
	t_object	*new_obj;
	t_real		diameter;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_obj->type = SPHERE;
	if (get_sphere_value(scene, line, new_obj, &diameter) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	new_obj->u_data.sphere.radius = diameter * 0.5;
	update_sphere_matrix(new_obj);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
