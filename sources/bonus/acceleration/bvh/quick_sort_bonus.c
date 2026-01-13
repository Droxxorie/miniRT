/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:54:59 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 17:45:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	cmp_x(const void *a, const void *b)
{
	t_object	*o1;
	t_object	*o2;
	t_real		val1;
	t_real		val2;

	o1 = *(t_object **)a;
	o2 = *(t_object **)b;
	val1 = get_box_center(o1->aabb, 0);
	val2 = get_box_center(o2->aabb, 0);
	return ((val1 > val2) - (val1 < val2));
}

static int	cmp_y(const void *a, const void *b)
{
	t_object	*o1;
	t_object	*o2;
	t_real		val1;
	t_real		val2;

	o1 = *(t_object **)a;
	o2 = *(t_object **)b;
	val1 = get_box_center(o1->aabb, 1);
	val2 = get_box_center(o2->aabb, 1);
	return ((val1 > val2) - (val1 < val2));
}

static int	cmp_z(const void *a, const void *b)
{
	t_object	*o1;
	t_object	*o2;
	t_real		val1;
	t_real		val2;

	o1 = *(t_object **)a;
	o2 = *(t_object **)b;
	val1 = get_box_center(o1->aabb, 2);
	val2 = get_box_center(o2->aabb, 2);
	return ((val1 > val2) - (val1 < val2));
}

static t_object	**list_to_array(t_object *head, int count)
{
	int			i;
	t_object	**array;

	if (count < 2)
		return (NULL);
	array = ft_calloc(count, sizeof(t_object *));
	if (!array)
		return (sys_print_error(ERR_MEM), NULL);
	i = 0;
	while (head)
	{
		if (head->visible == FALSE)
		{
			head = head->next;
			continue ;
		}
		array[i++] = head;
		head = head->next;
	}
	return (array);
}

void	sort_objects_axis(t_object **head, int axis)
{
	int			count;
	int			i;
	t_object	**array;
	t_object	*current;

	count = get_object_count(*head);
	array = list_to_array(*head, count);
	if (!array)
		return ;
	if (axis == 0)
		qsort(array, count, sizeof(t_object *), cmp_x);
	else if (axis == 1)
		qsort(array, count, sizeof(t_object *), cmp_y);
	else
		qsort(array, count, sizeof(t_object *), cmp_z);
	*head = array[0];
	current = *head;
	i = 0;
	while (++i < count)
	{
		current->next = array[i];
		current = current->next;
	}
	current->next = NULL;
	free(array);
}
