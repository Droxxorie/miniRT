/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:05:08 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 21:24:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	get_cylinder_value(t_scene *scene, char **line, t_object *obj)
{
	t_cylinder	*cyl;

	cyl = &obj->u_data.cylinder;
	if (parse_vec3(scene, line, &cyl->center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_axis(scene, line, &cyl->axis) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &cyl->radius) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line, &cyl->height) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_cylinder_matrix(t_object *object)
{
	t_mat4		translation;
	t_mat4		rotation;
	t_mat4		scaling;
	t_mat4		transform;
	t_cylinder	*cylinder;

	cylinder = &object->u_data.cylinder;
	translation = make_translation_matrix(cylinder->center);
	rotation = rotation_align(cylinder->axis);
	scaling = make_scale_matrix((t_vec3){
			cylinder->radius,
			cylinder->height,
			cylinder->radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}

t_status	parse_cylinder(t_scene *scene, char **line)
{
	t_object	*obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	obj = ft_calloc(1, sizeof(t_object));
	if (obj == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	obj->type = CYLINDER;
	if (get_cylinder_value(scene, line, obj) == EXIT_FAILURE)
		return (free(obj), EXIT_FAILURE);
	obj->u_data.cylinder.radius *= 0.5;
	init_cylinder_matrix(obj);
	add_object_to_scene(scene, obj);
	return (EXIT_SUCCESS);
}
