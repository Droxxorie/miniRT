/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_triangle_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:38:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 23:37:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_triangle(t_object *object, t_vec3 translation)
{
	t_triangle	*triangle;

	if (!object)
		return ;
	triangle = &object->u_data.triangle;
	triangle->p1 = vec3_add(triangle->p1, translation);
	triangle->p2 = vec3_add(triangle->p2, translation);
	triangle->p3 = vec3_add(triangle->p3, translation);
	update_object_matrix(object);
}
