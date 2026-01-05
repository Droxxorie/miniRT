/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:23:35 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 22:21:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static char	*get_window_title(t_scene *scene)
{
	char	*width_str;
	char	*height_str;
	char	*title;
	char	*temp;

	width_str = ft_itoa(scene->mlx_window.width);
	height_str = ft_itoa(scene->mlx_window.height);
	if (!width_str || !height_str)
	{
		free(width_str);
		free(height_str);
		return (NULL);
	}
	temp = ft_strjoin("miniRT - ", width_str);
	title = ft_strjoin(temp, "x");
	free(temp);
	temp = title;
	title = ft_strjoin(title, height_str);
	free(temp);
	free(width_str);
	free(height_str);
	return (title);
}

static t_status	init_frame_buffer(t_scene *scene)
{
	t_image	*image;

	image = &scene->frame_buffer;
	image->width = scene->mlx_window.width;
	image->height = scene->mlx_window.height;
	image->ptr = mlx_new_image(scene->mlx_window.mlx_ptr, image->width,
			image->height);
	if (!image->ptr)
		return (print_error(ERR_IMG), EXIT_FAILURE);
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
			return (print_error(ERR_MLX), EXIT_FAILURE);
	}
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->width,
			window->height, get_window_title(scene));
	if (!window->win_ptr)
		return (print_error(ERR_WIN), EXIT_FAILURE);
	if (init_frame_buffer(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
