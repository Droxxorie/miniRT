/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:27:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 14:18:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	add_camera_to_scene(t_scene *scene, t_camera *new_camera)
{
	t_camera	*current;

	if (scene->cameras == NULL)
		scene->cameras = new_camera;
	else
	{
		current = scene->cameras;
		while (current->next)
			current = current->next;
		current->next = new_camera;
	}
}

t_status	parse_camera(t_scene *scene, char **line)
{
	t_camera	*new_camera;
	int			fov;

	new_camera = ft_calloc(1, sizeof(t_camera));
	if (new_camera == NULL)
		return (sys_print_error(ERR_CAMERA_MEM), EXIT_FAILURE);
	if (parse_vec3(line, &new_camera->position) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(line, &new_camera->direction) == EXIT_FAILURE
		|| skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_int(line, &fov) == EXIT_FAILURE
		|| check_eol(line) == EXIT_FAILURE)
		return (free(new_camera), EXIT_FAILURE);
	new_camera->fov = fov;
	if (new_camera->fov <= 0 || new_camera->fov >= 180)
		return (free(new_camera), print_error(ERR_FOV_RANGE), EXIT_FAILURE);
	if (vec3_len_squared(new_camera->direction) == 0.0)
		return (free(new_camera), print_error(ERR_CAMERA_DIR), EXIT_FAILURE);
	new_camera->direction = vec3_normalize(new_camera->direction);
	new_camera->id = scene->camera_count++;
	add_camera_to_scene(scene, new_camera);
	return (EXIT_SUCCESS); // TODO NE PAS OUBLIER LES MATHS PLUS TARD HEIN !!!!!
}
