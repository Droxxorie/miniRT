/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:15:16 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 23:00:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	add_light_to_scene(t_scene *scene, t_light *new_light)
{
	t_light	*current;

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
	t_light	*new_light;

	if (get_light_count(scene->lights) >= MAX_LIGHTS)
		return (print_error_limit("lights", MAX_LIGHTS), EXIT_FAILURE);
	new_light = ft_calloc(1, sizeof(t_light));
	if (new_light == NULL)
		return (print_error(ERR_MEM_LIGHT), EXIT_FAILURE);
	if (parse_vec3(line, &new_light->position) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_ratio(line, &new_light->brightness, FALSE) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(line, &new_light->color) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_light), EXIT_FAILURE);
	add_light_to_scene(scene, new_light);
	return (EXIT_SUCCESS);
}
