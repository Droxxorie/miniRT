/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_post_filters_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:01:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	copy_temporary_buffer_to_frame(t_scene *scene, char *temporary_buf)
{
	size_t	buffer_size;

	buffer_size = (size_t)scene->frame_buffer.line_len
		* (size_t)scene->frame_buffer.height;
	ft_memcpy(scene->frame_buffer.addr, temporary_buf, buffer_size);
}

static void	run_convolution_filter(t_scene *scene, t_image *temporary_image,
	void (*filter_func)(t_image *, t_image *))
{
	filter_func(&scene->frame_buffer, temporary_image);
	copy_temporary_buffer_to_frame(scene, temporary_image->addr);
}

static void	run_convolution_filter_with_parameter(t_scene *scene,
	t_image *temporary_image,
	void (*filter_func)(t_image *, t_image *, t_real), t_real parameter)
{
	filter_func(&scene->frame_buffer, temporary_image, parameter);
	copy_temporary_buffer_to_frame(scene, temporary_image->addr);
}

static void	apply_single_filter_entry(t_scene *scene,
	t_filter_entry *current_filter_entry, t_image *temporary_image)
{
	t_image	*frame_buffer_image;

	frame_buffer_image = &scene->frame_buffer;
	if (current_filter_entry->type == FILTER_SOBEL)
		run_convolution_filter(scene, temporary_image, apply_filter_sobel);
	else if (current_filter_entry->type == FILTER_BNW)
		apply_filter_bnw(frame_buffer_image);
	else if (current_filter_entry->type == FILTER_GAUSSIAN)
		run_convolution_filter_with_parameter(scene, temporary_image,
			apply_filter_gaussian, current_filter_entry->param);
	else if (current_filter_entry->type == FILTER_SEPIA)
		apply_filter_sepia(frame_buffer_image);
	else if (current_filter_entry->type == FILTER_SHARPEN)
		run_convolution_filter_with_parameter(scene, temporary_image,
			apply_filter_sharpen, current_filter_entry->param);
	else if (current_filter_entry->type == FILTER_CONTRAST)
		apply_filter_contrast(frame_buffer_image, current_filter_entry->param);
	else if (current_filter_entry->type == FILTER_SATURATION)
		apply_filter_saturation(frame_buffer_image,
			current_filter_entry->param);
}

void	apply_post_filters(t_scene *scene)
{
	t_filter_entry	*current_filter_entry;
	char			*temporary_buffer;
	t_image			temporary_image;
	size_t			buffer_size;

	if (!scene || !scene->filters)
		return ;
	buffer_size = (size_t)scene->frame_buffer.line_len
		* (size_t)scene->frame_buffer.height;
	temporary_buffer = ft_calloc(1, buffer_size);
	if (!temporary_buffer)
		return ;
	temporary_image = (t_image){.ptr = NULL, .addr = temporary_buffer,
		.line_len = scene->frame_buffer.line_len,
		.bpp = scene->frame_buffer.bpp,
		.width = scene->frame_buffer.width,
		.height = scene->frame_buffer.height};
	current_filter_entry = scene->filters;
	while (current_filter_entry)
	{
		apply_single_filter_entry(scene, current_filter_entry,
			&temporary_image);
		current_filter_entry = current_filter_entry->next;
	}
	free(temporary_buffer);
}
