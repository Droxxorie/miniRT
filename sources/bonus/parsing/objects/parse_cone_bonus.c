/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:17:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 13:12:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_cone_values(t_scene *scene, char **line, t_object *object)
{
	t_cone	*cone;

	cone = &object->u_data.cone;
	if (parse_vec3(scene, line, &cone->base_center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line, &cone->axis) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &cone->radius) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &cone->height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &object->color) == EXIT_FAILURE
		|| parse_sdf(scene, line, &object->render_as_sdf) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_cone_matrix(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	transform;
	t_cone	*cone;

	cone = &object->u_data.cone;
	translation = make_translation_matrix(cone->base_center);
	rotation = rotation_align(cone->axis);
	scaling = make_scale_matrix((t_vec3){
			cone->radius,
			cone->height,
			cone->radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}

t_status	parse_cone(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (new_object == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = CONE;
	if (get_cone_values(scene, line, new_object) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	init_cone_matrix(new_object);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
