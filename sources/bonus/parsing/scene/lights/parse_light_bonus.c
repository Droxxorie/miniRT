/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:15:16 by eraad             #+#    #+#             */
/*   Updated: 2026/01/29 09:49:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_light(t_scene *scene, char **line)
{
	t_light	*light;

	light = alloc_new_light(scene, line);
	if (light == NULL)
		return (EXIT_FAILURE);
	light->type = LIGHT_POINT;
	if (parse_vec3(scene, line, &light->position) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->brightness) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &light->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(light), EXIT_FAILURE);
	add_light_to_scene(scene, light);
	return (EXIT_SUCCESS);
}

t_status	parse_sun(t_scene *scene, char **line)
{
	t_light	*light;

	light = alloc_new_light(scene, line);
	if (light == NULL)
		return (EXIT_FAILURE);
	light->type = LIGHT_SUN;
	if (parse_vec3(scene, line, &light->direction) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->brightness) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &light->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(light), EXIT_FAILURE);
	light->direction = vec3_normalize(light->direction);
	light->position = vec3_scale(light->direction, -10000);
	add_light_to_scene(scene, light);
	return (EXIT_SUCCESS);
}

t_status	parse_spot(t_scene *scene, char **line)
{
	t_light	*light;
	t_real	cutoff_angle;

	light = alloc_new_light(scene, line);
	if (light == NULL)
		return (EXIT_FAILURE);
	light->type = LIGHT_SPOT;
	if (parse_vec3(scene, line, &light->position) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line, &light->direction) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &cutoff_angle) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->brightness) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &light->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(light), EXIT_FAILURE);
	light->direction = vec3_normalize(light->direction);
	init_spot_light(light, cutoff_angle);
	add_light_to_scene(scene, light);
	return (EXIT_SUCCESS);
}

t_status	parse_quad(t_scene *scene, char **line)
{
	t_light	*light;

	light = alloc_new_light(scene, line);
	if (light == NULL)
		return (EXIT_FAILURE);
	light->type = LIGHT_QUAD;
	if (parse_vec3(scene, line, &light->position) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line, &light->direction) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->width) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &light->brightness) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &light->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(light), EXIT_FAILURE);
	light->direction = vec3_normalize(light->direction);
	init_quad_light(light);
	add_light_to_scene(scene, light);
	return (EXIT_SUCCESS);
}
