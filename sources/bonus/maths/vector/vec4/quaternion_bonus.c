/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:17:50 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 14:09:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec4	q_mult(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	return (result);
}

t_vec4	q_square(t_vec4 q)
{
	t_vec4	result;

	result.x = 2.0 * q.x * q.w;
	result.y = 2.0 * q.y * q.w;
	result.z = 2.0 * q.z * q.w;
	result.w = (q.w * q.w) - (q.x * q.x) - (q.y * q.y) - (q.z * q.z);
	return (result);
}

t_vec4	q_cube(t_vec4 q)
{
	t_vec4	q_sq;
	t_real	temp;
	t_vec4	result;

	q_sq = (t_vec4){q.x * q.x, q.y * q.y, q.z * q.z, q.w * q.w};
	result.x = q.x * (q_sq.x - 3.0 * q_sq.y - 3.0 * q_sq.z - 3.0 * q_sq.w);
	temp = 3.0 * q_sq.x - q_sq.y - q_sq.z - q_sq.w;
	result.y = q.y * temp;
	result.z = q.z * temp;
	result.w = q.w * temp;
	return (result);
}
