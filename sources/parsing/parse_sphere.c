/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:57:59 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 21:52:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	parse_sphere(t_scene *scene, char **line)
{
	t_objects	*new_object;
	t_real		diameter;

	new_object = ft_calloc(1, sizeof(t_objects));
	if (new_object == NULL)
		return (print_error(ERR_SPHERE_MEM), EXIT_FAILURE);
	new_object->type = SPHERE;
	if (parse_vec3(line, &new_object->data.sphere.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &diameter) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &new_object->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	if (diameter <= 0)
		return (free(new_object), print_error(ERR_PARSE_SP_D), EXIT_FAILURE);
	new_object->data.sphere.radius = diameter * 0.5;
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
