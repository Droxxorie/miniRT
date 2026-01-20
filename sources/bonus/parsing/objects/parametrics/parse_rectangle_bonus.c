/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rectangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:34:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 15:04:12 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	print_rectangle_syntax(void)
{
	log_event(stdout, "INFO",
		"Rectangle syntax:\n\t<%s> <%s> <%s> <%s> <%s> [options]\n",
		"Center x,y,z", "Normal x,y,z", "Width", "Height", "Color r,g,b");
}

static t_status	get_rectangle_values(t_scene *scene, char **line,
		t_object *object)
{
	if (parse_vec3(scene, line,
			&object->u_data.rectangle.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line,
			&object->u_data.rectangle.normal) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &object->u_data.rectangle.width) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_real(line, &object->u_data.rectangle.height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &object->color) == EXIT_FAILURE
		|| parse_options(scene, line, object) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (print_rectangle_syntax(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_rectangle_matrix(t_object *object)
{
	t_mat4		translation;
	t_mat4		rotation;
	t_mat4		scaling;
	t_mat4		transform;
	t_rectangle	*rectangle;

	rectangle = &object->u_data.rectangle;
	translation = make_translation_matrix(rectangle->center);
	rotation = rotation_align(rectangle->normal);
	scaling = make_scale_matrix((t_vec3){rectangle->width, 1.0,
			rectangle->height});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}

t_status	parse_rectangle(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (new_object == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = RECTANGLE;
	if (get_rectangle_values(scene, line, new_object) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	init_rectangle_matrix(new_object);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
