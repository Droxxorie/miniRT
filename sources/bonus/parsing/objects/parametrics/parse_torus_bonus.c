/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_torus_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:07:13 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 14:20:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	print_torus_syntax(void)
{
	log_event(stdout, "INFO",
		"Torus syntax:\n\t<%s> <%s> <%s> <%s> <%s> [options]\n", "Center x,y,z",
		"Normal x,y,z", "Major Radius", "Minor Radius", "Color r,g,b");
}

static t_status	get_torus_values(t_scene *scene, char **line, t_object *obj)
{
	if (parse_vec3(scene, line, &obj->u_data.torus.center) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line, &obj->u_data.torus.axis) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line,
			&obj->u_data.torus.major_radius) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_dim(scene, line,
			&obj->u_data.torus.minor_radius) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &obj->color) == EXIT_FAILURE
		|| parse_options(scene, line, obj) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (print_torus_syntax(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_torus_vars(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	transform;
	t_torus	*torus;

	torus = &object->u_data.torus;
	torus->major_radius_sq = torus->major_radius * torus->major_radius;
	torus->minor_radius_sq = torus->minor_radius * torus->minor_radius;
	torus->diff_radius_sq = torus->major_radius_sq - torus->minor_radius_sq;
	translation = make_translation_matrix(torus->center);
	rotation = rotation_align(torus->axis);
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	set_transform(object, transform);
}

t_status	parse_torus(t_scene *scene, char **line)
{
	t_object	*new_obj;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_obj = ft_calloc(1, sizeof(t_object));
	if (new_obj == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_obj->type = TORUS;
	if (get_torus_values(scene, line, new_obj) == EXIT_FAILURE)
		return (free(new_obj), EXIT_FAILURE);
	init_torus_vars(new_obj);
	add_object_to_scene(scene, new_obj);
	return (EXIT_SUCCESS);
}
