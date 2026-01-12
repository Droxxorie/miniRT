/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:26:28 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 16:09:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

char	*get_object_type_str(t_object_type type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else if (type == RECTANGLE)
		return ("RECTANGLE");
	else if (type == DISK)
		return ("DISK");
	else if (type == TRIANGLE)
		return ("TRIANGLE");
	else if (type == TORUS)
		return ("TORUS");
	else if (type == CONE)
		return ("CONE");
	else if (type == BOX)
		return ("BOX");
	else
		return ("NONE");
}

void	get_scale_and_position(t_object *object, t_vec3 *s, t_vec3 *p,
		t_color *c)
{
	t_mat4	t;

	t = object->transform;
	*p = (t_vec3){t.m[0][3], t.m[1][3], t.m[2][3]};
	s->x = sqrt(t.m[0][0] * t.m[0][0] + t.m[0][1] * t.m[0][1] + t.m[0][2]
			* t.m[0][2]);
	s->y = sqrt(t.m[1][0] * t.m[1][0] + t.m[1][1] * t.m[1][1] + t.m[1][2]
			* t.m[1][2]);
	s->z = sqrt(t.m[2][0] * t.m[2][0] + t.m[2][1] * t.m[2][1] + t.m[2][2]
			* t.m[2][2]);
	c->r = object->color.r * 255;
	c->g = object->color.g * 255;
	c->b = object->color.b * 255;
}
