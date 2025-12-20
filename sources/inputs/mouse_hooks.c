/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:13:58 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 13:24:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	handle_left_click(t_scene *scene, int x, int y)
{
	t_ray			ray;
	t_hit_record	record;

	scene->selected_object = NULL;
	scene->selected_light = NULL;
	generate_ray(scene->active_camera, &ray, (t_real)x, (t_real)y);
	// if (try_select_light(scene, &ray))
	// 	return ;
	if (hit_objects(scene->objects, &ray, &record) && record.object != scene->selected_object)
	{
		scene->selected_object = record.object;
		ft_putstr_fd("Switched to object control mode\n", 1);
		print_object_details(record.object->type);
	}
}

static void	handle_right_click(t_scene *scene)
{
	if (scene->selected_object != NULL || scene->selected_light != NULL)
	{
		scene->selected_object = NULL;
		scene->selected_light = NULL;
		ft_putstr_fd("Switched to camera control mode\n", 1);
		ft_putstr_fd("Camera ID: ", 1);
		ft_putnbr_fd(scene->active_camera->id, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
}

static void	handle_scroll(int button, t_scene *scene)
{
	int	mode;
	int	direction;

	if (scene->selected_object == NULL)
		return ;
	if (button == SCROLL_UP)
		direction = 1;
	else if (button == SCROLL_DOWN)
		direction = -1;
	else
		return ;
	if (scene->shift_pressed == TRUE)
		mode = RESIZE_HEIGHT;
	else
		mode = RESIZE_RADIUS;
	dispatch_resize(scene->selected_object, mode, direction);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	t_bool	render_needed;

	render_needed = FALSE;
	if (button == RIGHT_CLICK)
		handle_right_click(scene);
	else if (button == LEFT_CLICK)
		handle_left_click(scene, x, y);
	else if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		render_needed = TRUE;
		handle_scroll(button, scene);
	}
	if (render_needed == TRUE)
		render_frame(scene);
	return (EXIT_SUCCESS);
}
