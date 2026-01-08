/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_disk_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:44:13 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 21:44:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	save_disk_state(t_disk *disk)
{
	disk->initial_center = disk->center;
	disk->initial_normal = disk->normal;
	disk->initial_radius = disk->radius;
}
