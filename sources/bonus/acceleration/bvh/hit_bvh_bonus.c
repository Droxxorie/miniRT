/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:31:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 19:26:11 by eraad            ###   ########.fr       */
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
	t_bool		hit[2];
	t_bvh_node	*first;
	t_bvh_node	*second;

	if (!node || hit_aabb(&node->box, ray, ray->min, ray->max) == FALSE)
		return (FALSE);
	if (node->left_child == NULL && node->right_child == NULL)
	{
		if (hit_aabb(&node->box, ray, ray->min, ray->max) == FALSE)
			return (FALSE);
		return (hit_leaf_content(node->content, ray, record) == TRUE);
	}
	first = node->right_child;
	second = node->left_child;
	if (get_axis_value(ray->direction, node->axis) >= 0)
	{
		first = node->left_child;
		second = node->right_child;
	}
	hit[0] = hit_bvh(first, ray, record);
	hit[1] = hit_bvh(second, ray, record);
	return (hit[0] || hit[1]);
}
