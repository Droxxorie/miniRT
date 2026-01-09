/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_triangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:06:43 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 14:24:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_triangle(t_object *object)
{
	t_triangle	*triangle;

	triangle = &object->u_data.triangle;
	triangle->edge1 = vec3_sub(triangle->p2, triangle->p1);
	triangle->edge2 = vec3_sub(triangle->p3, triangle->p1);
	triangle->normal = vec3_normalize(vec3_cross(triangle->edge1,
				triangle->edge2));
}
