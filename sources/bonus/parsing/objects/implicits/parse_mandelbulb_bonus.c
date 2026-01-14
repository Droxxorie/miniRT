/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mandelbulb_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:11:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:58:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	print_mandelbulb_syntax(void)
{
	log_event(stdout, "INFO",
		"Mandelbulb syntax:\n\t<%s> <%s> <%s> <%s> <%s>\n", "Position x,y,z",
		"Normal x,y,z", "Size", "Power", "Color r,g,b");
}

static t_status	get_mandelbulb_values(t_scene *scene, char **line,
		t_object *obj)
{
	if (parse_vec3(scene, line,
			&obj->u_data.mandelbulb.postition) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line,
			&obj->u_data.mandelbulb.normal) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &obj->u_data.mandelbulb.size) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &obj->u_data.mandelbulb.power) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (print_mandelbulb_syntax(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_mandelbulb(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (!new_object)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = MANDELBULB;
	new_object->render_as_sdf = TRUE;
	new_object->is_fractal = TRUE;
	if (get_mandelbulb_values(scene, line, new_object) == EXIT_FAILURE)
	{
		free(new_object);
		return (EXIT_FAILURE);
	}
	init_fractal_matrix(new_object, new_object->u_data.mandelbulb.postition,
		new_object->u_data.mandelbulb.normal,
		new_object->u_data.mandelbulb.size);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
