/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_triangle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:32:35 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 08:54:47 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_triangle_state(t_object *object)
{
	object->u_data.triangle.p1 = object->u_data.triangle.initial_p1;
	object->u_data.triangle.p2 = object->u_data.triangle.initial_p2;
	object->u_data.triangle.p3 = object->u_data.triangle.initial_p3;
	update_object(object);
}
