/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:49:32 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:51:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_plane_values(t_scene *scene, char **line, t_object *obj)
{
	if (parse_vec3(scene, line, &obj->u_data.rectangle.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line,
			&obj->u_data.rectangle.normal) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| parse_sdf(scene, line, &obj->render_as_sdf) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_plane_matrix(t_object *object)
{
	t_mat4		translation;
	t_mat4		rotation;
	t_mat4		scale;
	t_mat4		transform;
	t_rectangle	*plane;

	plane = &object->u_data.rectangle;
	translation = make_translation_matrix(plane->center);
	rotation = rotation_align(plane->normal);
	scale = make_scale_matrix((t_vec3){PLANE_SCALE, 1.0, PLANE_SCALE});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scale);
	set_transform(object, transform);
}

t_status	parse_plane(t_scene *scene, char **line)
{
	t_object	*new_obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_obj->type = RECTANGLE;
	if (get_plane_values(scene, line, new_obj) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	init_plane_matrix(new_obj);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
