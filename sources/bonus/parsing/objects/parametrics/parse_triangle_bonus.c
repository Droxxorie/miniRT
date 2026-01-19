/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:59:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 10:01:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	print_triangle_syntax(void)
{
	log_event(stdout, "INFO",
		"Triangle syntax:\n\t<%s> <%s> <%s> <%s>\n", "Point 1 x,y,z",
		"Point 2 x,y,z", "Point 3 x,y,z", "Color r,g,b");
}

static t_status	get_triangle_values(t_scene *scene, char **line,
		t_object *object)
{
	if (parse_vec3(scene, line, &object->u_data.triangle.p1) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line, &object->u_data.triangle.p2) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_vec3(scene, line, &object->u_data.triangle.p3) == EXIT_FAILURE
		|| skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE
		|| parse_color(scene, line, &object->color) == EXIT_FAILURE
		|| parse_sdf(scene, line, &object->render_as_sdf) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (print_triangle_syntax(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_triangle_matrix(t_object *object)
{
	t_triangle	*triangle;
	t_vec3		center;
	t_mat4		transform;

	triangle = &object->u_data.triangle;
	center = vec3_add(triangle->p1, triangle->p2);
	center = vec3_add(center, triangle->p3);
	center = vec3_scale(center, 1.0 / 3.0);
	triangle->p1 = vec3_sub(triangle->p1, center);
	triangle->p2 = vec3_sub(triangle->p2, center);
	triangle->p3 = vec3_sub(triangle->p3, center);
	triangle->edge1 = vec3_sub(triangle->p2, triangle->p1);
	triangle->edge2 = vec3_sub(triangle->p3, triangle->p1);
	triangle->normal = vec3_normalize(vec3_cross(triangle->edge1,
				triangle->edge2));
	transform = make_translation_matrix(center);
	set_transform(object, transform);
}

t_status	parse_triangle(t_scene *scene, char **line)
{
	t_object	*new_object;

	if (get_object_count(scene->objects) >= MAX_OBJECTS)
		return (print_error_limit(scene, *line - 1, "objects", MAX_OBJECTS),
			EXIT_FAILURE);
	new_object = ft_calloc(1, sizeof(t_object));
	if (new_object == NULL)
		return (print_error(ERR_MEM_OBJECT), EXIT_FAILURE);
	new_object->type = TRIANGLE;
	if (get_triangle_values(scene, line, new_object) == EXIT_FAILURE)
		return (free(new_object), EXIT_FAILURE);
	init_triangle_matrix(new_object);
	add_object_to_scene(scene, new_object);
	return (EXIT_SUCCESS);
}
