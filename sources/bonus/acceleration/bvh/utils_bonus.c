/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:59:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 13:00:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	get_box_center(t_aabb box, int axis)
{
	t_point3	center;
	t_point3	min;
	t_point3	max;

	min = box.min;
	max = box.max;
	center.x = min.x + (max.x - min.x) * 0.5;
	center.y = min.y + (max.y - min.y) * 0.5;
	center.z = min.z + (max.z - min.z) * 0.5;
	if (axis == 0)
		return (center.x);
	else if (axis == 1)
		return (center.y);
	else
		return (center.z);
}

static void	free_bvh(t_bvh_node *node)
{
	if (!node)
		return ;
	free_bvh(node->left_child);
	free_bvh(node->right_child);
	free(node);
}

static void	flatten_bvh(t_bvh_node *node, t_object **tail)
{
	t_object	*current;

	if (!node)
		return ;
	if (node->left_child == NULL && node->right_child == NULL)
	{
		if (node->content)
		{
			(*tail)->next = node->content;
			current = node->content;
			while (current->next)
				current = current->next;
			*tail = current;
		}
		return ;
	}
	flatten_bvh(node->left_child, tail);
	flatten_bvh(node->right_child, tail);
}

void	destroy_bvh(t_scene *scene)
{
	t_object	*tail;
	t_object	temp;

	if (!scene || !scene->bvh_root)
		return ;
	ft_bzero(&temp, sizeof(t_object));
	tail = &temp;
	flatten_bvh(scene->bvh_root, &tail);
	if (tail)
		tail->next = NULL;
	scene->objects = temp.next;
	free_bvh(scene->bvh_root);
	scene->bvh_root = NULL;
}

void	refresh_bvh(t_scene *scene, t_object *object)
{
	t_object	*head;
	t_object	*tail;
	t_object	temp;

	if (!scene || !scene->bvh_root)
		return ;
	ft_bzero(&temp, sizeof(t_object));
	head = &temp;
	tail = head;
	flatten_bvh(scene->bvh_root, &tail);
	scene->objects = head->next;
	free_bvh(scene->bvh_root);
	scene->bvh_root = NULL;
	if (object)
		compute_object_bounds(object);
	build_bvh(scene);
}
