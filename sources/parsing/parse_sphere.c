/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:57:59 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 23:02:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	get_sphere_value(char **line, t_object *obj, t_real *d)
{
	if (parse_vec3(line, &obj->u_data.sphere.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, d) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &obj->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_sphere(t_scene *scene, char **line)
{
	t_object	*new_obj;
	t_real		diameter;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit("objects", MAX_OBJECTS), EXIT_FAILURE);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_MEM_SPHERE), EXIT_FAILURE);
	new_obj->type = SPHERE;
	if (get_sphere_value(line, new_obj, &diameter) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	if (diameter <= 0)
		return (free(new_obj), print_error(ERR_PARSE_SP_D), EXIT_FAILURE);
	new_obj->u_data.sphere.radius = diameter * 0.5;
	new_obj->u_data.sphere.radius_squared = new_obj->u_data.sphere.radius
		* new_obj->u_data.sphere.radius;
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
