/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 21:44:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	log_info(const char *message)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_CYAN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	if (message)
		ft_putstr_fd((char *)message, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	log_detail(const char *message, const char *detail)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_CYAN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	if (message)
		ft_putstr_fd((char *)message, STDOUT_FILENO);
	if (detail)
	{
		ft_putstr_fd(UNDERLINE, STDOUT_FILENO);
		ft_putstr_fd((char *)detail, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	log_scene_stats(t_scene *scene)
{
	int	object_count;
	int	light_count;
	int	camera_count;

	object_count = get_object_count(scene->objects);
	light_count = get_light_count(scene->lights);
	camera_count = get_camera_count(scene->cameras);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_CYAN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	ft_putstr_fd("Scene Statistics:", STDOUT_FILENO);
	ft_putstr_fd("  Objects: ", STDOUT_FILENO);
	ft_putnbr_fd(object_count, STDOUT_FILENO);
	ft_putstr_fd("  Lights: ", STDOUT_FILENO);
	ft_putnbr_fd(light_count, STDOUT_FILENO);
	ft_putstr_fd("  Cameras: ", STDOUT_FILENO);
	ft_putnbr_fd(camera_count, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
