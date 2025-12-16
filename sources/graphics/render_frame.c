/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 16:10:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	render_frame(t_scene *scene)
{
	render_scene(scene);
	if (scene->mlx_window.mlx_win)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.mlx_win,
			scene->frame_buffer.ptr, 0, 0);
	return (EXIT_SUCCESS);
}
