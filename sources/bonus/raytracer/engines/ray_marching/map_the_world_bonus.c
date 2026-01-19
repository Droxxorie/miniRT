/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_the_world_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:24:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 16:54:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	get_min_dist_in_leaf(t_object *object, t_point3 world_p)
{
	t_real	min_dist;
	t_real	dist;

	if (!object || object->visible == FALSE)
		return (INFINITY);
	min_dist = INFINITY;
	while (object)
	{
		dist = dispatch_sdf(world_p, object) * object->sdf_scale;
		if (dist < min_dist)
			min_dist = dist;
		object = object->next;
	}
	return (min_dist);
}

static t_real	map_bvh_recursive(t_bvh_node *node, t_point3 world_p)
{
	t_real	left_dist;
	t_real	right_dist;

	if (!node)
		return (INFINITY);
	if (node->left_child == NULL && node->right_child == NULL)
		return (get_min_dist_in_leaf(node->content, world_p));
	left_dist = map_bvh_recursive(node->left_child, world_p);
	right_dist = map_bvh_recursive(node->right_child, world_p);
	return (fmin(left_dist, right_dist));
}

t_real	map_the_world(t_point3 world_p, t_scene *scene)
{
	return (map_bvh_recursive(scene->bvh_root, world_p));
}
