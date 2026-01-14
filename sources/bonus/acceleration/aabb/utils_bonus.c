/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:53:16 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:53:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	empty_aabb(void)
{
	t_aabb	box;

	box.min = (t_point3){INFINITY, INFINITY, INFINITY};
	box.max = (t_point3){-INFINITY, -INFINITY, -INFINITY};
	return (box);
}

void	grow_aabb(t_aabb *box, t_point3 point)
{
	box->min.x = fmin(box->min.x, point.x);
	box->min.y = fmin(box->min.y, point.y);
	box->min.z = fmin(box->min.z, point.z);
	box->max.x = fmax(box->max.x, point.x);
	box->max.y = fmax(box->max.y, point.y);
	box->max.z = fmax(box->max.z, point.z);
}

t_aabb	surrounding_box(t_aabb box1, t_aabb box2)
{
	t_aabb	surround_box;

	surround_box.min.x = fmin(box1.min.x, box2.min.x);
	surround_box.min.y = fmin(box1.min.y, box2.min.y);
	surround_box.min.z = fmin(box1.min.z, box2.min.z);
	surround_box.max.x = fmax(box1.max.x, box2.max.x);
	surround_box.max.y = fmax(box1.max.y, box2.max.y);
	surround_box.max.z = fmax(box1.max.z, box2.max.z);
	return (surround_box);
}
