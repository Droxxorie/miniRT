/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_torus_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:03:25 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 23:30:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_torus(t_point3 p, t_real major_r, t_real minor_r)
{
	t_vec2	q;

	q.x = vec2_len((t_vec2){p.x, p.z}) - major_r;
	q.y = p.y;
	return (vec2_len(q) - minor_r);
}
