/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 12:56:59 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	ft_putstr_fd("Scene Statistics:\n", STDOUT_FILENO);
	ft_putstr_fd("  Objects: ", STDOUT_FILENO);
	ft_putnbr_fd(object_count, STDOUT_FILENO);
	ft_putstr_fd("  Lights: ", STDOUT_FILENO);
	ft_putnbr_fd(light_count, STDOUT_FILENO);
	ft_putstr_fd("  Cameras: ", STDOUT_FILENO);
	ft_putnbr_fd(camera_count, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("  Resolution: ", STDOUT_FILENO);
	ft_putnbr_fd(scene->mlx_window.width, STDOUT_FILENO);
	ft_putstr_fd("x", STDOUT_FILENO);
	ft_putnbr_fd(scene->mlx_window.height, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}


void	log_event(char *type, char *message, int detail)
{
    time_t      now;
    struct tm   *local;
    char        *color;

    now = time(NULL);
    local = localtime(&now);
	printf("[%s%02i:%02i:%02i%s] ", RED, local->tm_hour, local->tm_min, local->tm_sec, RESET);
    if (ft_strncmp(type, "ERROR", 5) == 0)
        color = RED;
    else if (ft_strncmp(type, "SUCCESS", 7) == 0)
        color = GREEN;
    else if (ft_strncmp(type, "PERF", 4) == 0)
        color = MAGENTA;
    else if (ft_strncmp(type, "WARN", 4) == 0)
        color = YELLOW;
    else if (ft_strncmp(type, "INFO", 4) == 0)
        color = B_BLUE;
	else
		color = CYAN;
	printf("[%s%s%s] %s", color, type, RESET, message);
	if (detail)
		printf("%i", detail);
	printf("\n");
}

char *get_object_type_string(t_object_type type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else
		return ("NONE");
}

void	log_event_object(char *type, char *message, t_object_type object_type)
{
	char *temp;

	temp = get_object_type_string(object_type);
	temp = ft_strjoin(message, temp);
	if (object_type == SPHERE)
		log_event(type, temp, 0);
	else if (object_type == PLANE)
		log_event(type, temp, 0);
	else if (object_type == CYLINDER)
		log_event(type, temp, 0);
	else
		log_event(type, temp, 0);
	free(temp);
}
