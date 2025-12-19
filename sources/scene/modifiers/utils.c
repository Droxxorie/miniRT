/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:33 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 22:32:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_transform(t_object *object, t_mat4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse = mat4_inverse(object->transform);
	object->transposed_inverse = mat4_transpose(object->inverse);
}
