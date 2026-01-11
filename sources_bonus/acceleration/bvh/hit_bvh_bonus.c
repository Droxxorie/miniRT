/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:31:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 00:07:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	get_axis_value(t_vec3 v, int axis)
{
	if (axis == 0)
		return (v.x);
	else if (axis == 1)
		return (v.y);
	else
		return (v.z);
}

static t_bool	hit_leaf_content(t_object *objects, t_ray *ray,
		t_hit_record *record)
{
	t_bool			hit_anything;
	t_object		*temp;
	t_hit_record	temp_record;

	hit_anything = FALSE;
	temp = objects;
	temp_record.need_details = record->need_details;
	while (temp)
	{
		if (temp->visible == FALSE)
		{
			temp = temp->next;
			continue ;
		}
		if (hit_dispatch(temp, ray, &temp_record))
		{
			hit_anything = TRUE;
			ray->max = temp_record.t;
			*record = temp_record;
		}
		temp = temp->next;
	}
	return (hit_anything);
}

t_bool	hit_bvh(t_bvh_node *node, t_ray *ray, t_hit_record *record)
{
	t_bool		hit_first;
	t_bool		hit_second;
	t_bvh_node	*first;
	t_bvh_node	*second;

	if (!node || !hit_aabb(&node->box, ray, ray->min, ray->max))
		return (FALSE);
	if (node->left_child == NULL && node->right_child == NULL)
		return (hit_leaf_content(node->content, ray, record));
	if (get_axis_value(ray->direction, node->axis) >= 0)
	{
		first = node->left_child;
		second = node->right_child;
	}
	else
	{
		first = node->right_child;
		second = node->left_child;
	}
	hit_first = hit_bvh(first, ray, record);
	hit_second = hit_bvh(second, ray, record);
	return (hit_first || hit_second);
}
