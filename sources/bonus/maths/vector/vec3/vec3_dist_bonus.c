/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dist_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:28:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:28:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	vec3_dist(t_point3 p1, t_point3 p2)
{
	t_vec3	diff;

	diff = vec3_sub(p2, p1);
	return (sqrtf(vec3_dot(diff, diff)));
}
