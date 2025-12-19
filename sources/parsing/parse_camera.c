/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:27:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 20:19:23 by eraad            ###   ########.fr       */
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

static t_status	parse_fov(t_scene *scene, char **line, int *fov)
{
	char	*start_line;

	skip_whitespace(line);
	start_line = *line;
	if (parse_int(line, fov) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_FOV), EXIT_FAILURE);
	if (*fov <= 0 || *fov >= 180)
		return (print_error_loc(scene, start_line, ERR_FOV_OOR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_camera(t_scene *scene, char **line)
{
	t_camera	*new_camera;

	if (get_camera_count(scene->cameras) >= MAX_CAMERAS)
		return (print_error_limit(scene, *line - 1, "cameras", MAX_CAMERAS),
			EXIT_FAILURE);
	new_camera = ft_calloc(1, sizeof(t_camera));
	if (new_camera == NULL)
		return (sys_print_error(ERR_MEM_CAMERA), EXIT_FAILURE);
	if (parse_vec3(scene, line, &new_camera->position) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line, &new_camera->direction) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_fov(scene, line, &new_camera->fov) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(new_camera), EXIT_FAILURE);
	new_camera->width = (t_real)WINDOW_WIDTH;
	new_camera->height = (t_real)WINDOW_HEIGHT;
	new_camera->aspect_ratio = (t_real)new_camera->width
		/ (t_real)new_camera->height;
	add_camera_to_scene(scene, new_camera);
	return (EXIT_SUCCESS);
}
