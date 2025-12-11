/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 18:48:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	render_frame(t_scene *scene)
{
	int	x;
	int	y;
	t_real	u;
	t_real	v;

	x = 0;
	y = 0;
	u = 0.0;
	v = 0.0;
	render_scene(scene, x, y, u, v); // TODO
	if (scene->mlx_window.mlx_win)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.mlx_win,
			scene->frame_buffer.ptr, 0, 0); // TODO check return ?
	return (EXIT_SUCCESS);
}
