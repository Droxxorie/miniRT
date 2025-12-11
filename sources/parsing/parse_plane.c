/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:49:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:28:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	parse_plane(t_scene *scene, char **line)
{
	t_object	*new_obj;

	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_PLANE_MEM), EXIT_FAILURE);
	new_obj->type = PLANE;
	if (parse_vec3(line, &new_obj->data.plane.origin) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &new_obj->data.plane.normal) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &new_obj->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	if (vec3_len_squared(new_obj->data.plane.normal) == 0)
		return (free(new_obj), print_error(ERR_PARSE_PL_N), EXIT_FAILURE);
	new_obj->data.plane.normal = vec3_normalize(new_obj->data.plane.normal);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
