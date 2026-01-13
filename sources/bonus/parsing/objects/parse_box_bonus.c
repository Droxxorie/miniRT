/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_box_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:10:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 13:12:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_box_values(t_scene *scene, char **line, t_object *object)
{
	t_box	*box;

	box = &object->u_data.box;
	if (parse_vec3(scene, line, &box->center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line, &box->axis) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &box->width) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &box->height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &box->depth) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &object->color) == EXIT_FAILURE
		|| parse_sdf(scene, line, &object->render_as_sdf) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_box_matrix(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	transform;
	t_box	*box;

	box = &object->u_data.box;
	translation = make_translation_matrix(box->center);
	rotation = rotation_align(box->axis);
	scaling = make_scale_matrix((t_vec3){box->width, box->height, box->depth});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}

t_status	parse_box(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (new_object == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = BOX;
	if (get_box_values(scene, line, new_object) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	init_box_matrix(new_object);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
