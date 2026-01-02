/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_pixel_put_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:47:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:39:47 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	image_pixel_put(t_image *image, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	pixel_addr = image->addr + ((y * image->line_len) + (x * (image->bpp / 8)));
	*(unsigned int *)pixel_addr = color;
}
