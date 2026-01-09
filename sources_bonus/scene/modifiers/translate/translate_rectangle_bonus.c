/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_rectangle_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:42:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:16:32 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_rectangle(t_object *object, t_vec3 translation)
{
	t_rectangle	*rectangle;

	if (!object)
		return ;
	rectangle = &object->u_data.rectangle;
	rectangle->center = vec3_add(rectangle->center, translation);
	update_object(object);
}
