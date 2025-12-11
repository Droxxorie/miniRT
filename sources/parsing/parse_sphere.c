/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:57:59 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:29:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	parse_sphere(t_scene *scene, char **line)
{
	t_object	*new_obj;
	t_real		diameter;

	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_SPHERE_MEM), EXIT_FAILURE);
	new_obj->type = SPHERE;
	if (parse_vec3(line, &new_obj->data.sphere.center) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &diameter) == EXIT_FAILURE || skip_required(line,
			WHITESPACE_CHARS) == EXIT_FAILURE || parse_color(line,
			&new_obj->color) == EXIT_FAILURE || check_eol(line) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	if (diameter <= 0)
		return (free(new_obj), print_error(ERR_PARSE_SP_D), EXIT_FAILURE);
	new_obj->data.sphere.radius = diameter * 0.5;
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
