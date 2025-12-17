/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:23:35 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 21:33:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	init_frame_buffer(t_scene *scene)
{
	t_image	*image;

	image = &scene->frame_buffer;
	image->width = scene->mlx_window.width;
	image->height = scene->mlx_window.height;
	image->ptr = mlx_new_image(scene->mlx_window.mlx_ptr, image->width,
			image->height);
	if (!image->ptr)
		return (print_error(ERR_INIT_FB), EXIT_FAILURE);
	image->addr = mlx_get_data_addr(image->ptr, &image->bpp, &image->line_len,
			&image->endian);
	return (EXIT_SUCCESS);
}

t_status	init_graphics(t_scene *scene)
{
	t_window	*window;

	window = &scene->mlx_window;
	if (!window->mlx_ptr)
	{
		window->mlx_ptr = mlx_init();
		if (!window->mlx_ptr)
			return (print_error(ERR_INIT_MLX), EXIT_FAILURE);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->width,
			window->height, "miniRT");
	if (!window->win_ptr)
		return (print_error(ERR_INIT_WIN), EXIT_FAILURE);
	if (init_frame_buffer(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
