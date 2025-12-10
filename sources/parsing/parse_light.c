/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:15:16 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 18:20:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void add_light_to_scene(t_scene *scene, t_lights *new_light)
{
	t_lights *current;

	if (scene->lights == NULL)
		scene->lights = new_light;
	else
	{
		current = scene->lights;
		while (current->next)
			current = current->next;
		current->next = new_light;
	}
}

t_status	parse_light(t_scene *scene, char **line)
{
	t_lights	*new_light;

	new_light = ft_calloc(1, sizeof(t_lights));
	if (new_light == NULL)
		return (print_error(ERR_LIGHT_MEM), EXIT_FAILURE);
	if (parse_vec3(line, &new_light->position) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_ratio(line, &new_light->brightness, FALSE) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &new_light->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_light), EXIT_FAILURE);
	new_light->color = color_scale(new_light->color, new_light->brightness);
	add_light_to_scene(scene, new_light);
	return (EXIT_SUCCESS);
}
