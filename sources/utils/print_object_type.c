/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:30:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 22:30:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_object_type(t_object_type type)
{
	if (type == SPHERE)
		ft_putstr_fd("Object Type: SPHERE\n", 1);
	else if (type == PLANE)
		ft_putstr_fd("Object Type: PLANE\n", 1);
	else if (type == CYLINDER)
		ft_putstr_fd("Object Type: CYLINDER\n", 1);
	else
		ft_putstr_fd("Object Type: NONE\n", 1);
}
