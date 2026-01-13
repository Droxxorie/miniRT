/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_dispatch_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:24:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 17:30:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	hit_dispatch(t_object *object, t_ray *ray, t_hit_record *record)
{
	if (object->render_as_sdf) //TODO ajouter ici pour fractals
		return (ray_march(object, ray, record));
	else
		return (ray_tracing(object, ray, record));
}
