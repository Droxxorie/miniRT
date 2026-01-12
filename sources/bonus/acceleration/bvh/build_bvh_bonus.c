/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bvh_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:06:24 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 00:07:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_aabb	compute_list_bounds(t_object *objects)
{
	t_aabb	box;

	box = empty_aabb();
	while (objects)
	{
		box = surrounding_box(box, objects->aabb);
		objects = objects->next;
	}
	return (box);
}

static int	get_longest_axis(t_aabb box)
{
	t_real	x_len;
	t_real	y_len;
	t_real	z_len;

	x_len = box.max.x - box.min.x;
	y_len = box.max.y - box.min.y;
	z_len = box.max.z - box.min.z;
	if (x_len >= y_len && x_len >= z_len)
		return (0);
	else if (y_len >= z_len)
		return (1);
	else
		return (2);
}

static t_object	*split_list(t_object *head, int count)
{
	t_object	*current;
	t_object	*right_list;
	int			mid;
	int			i;

	mid = count / 2;
	current = head;
	i = -1;
	while (++i < mid - 1)
		current = current->next;
	right_list = current->next;
	current->next = NULL;
	return (right_list);
}

static t_bvh_node	*recursive_build(t_object *objects, int count)
{
	t_bvh_node	*node;
	t_object	*left_list;
	t_object	*right_list;
	int			axis;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (sys_print_error(ERR_MEM), NULL);
	node->box = compute_list_bounds(objects);
	if (count < 2)
	{
		node->content = objects;
		node->left_child = NULL;
		node->right_child = NULL;
		return (node);
	}
	axis = get_longest_axis(node->box);
	node->axis = axis;
	sort_objects_axis(&objects, axis);
	right_list = split_list(objects, count);
	left_list = objects;
	node->left_child = recursive_build(left_list, count / 2);
	node->right_child = recursive_build(right_list, count - (count / 2));
	return (node);
}

void	build_bvh(t_scene *scene)
{
	int			count;
	t_object	*current;

	if (!scene || !scene->objects)
		return ;
	current = scene->objects;
	while (current)
	{
		compute_object_bounds(current);
		current = current->next;
	}
	count = get_object_count(scene->objects);
	scene->bvh_root = recursive_build(scene->objects, count);
	scene->objects = NULL;
}
