/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 23:08:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	log_event(char *type, char *format, ...)
{
	va_list		args;
	time_t		now;
	struct tm	*local;
	char		*color;

	now = time(NULL);
	local = localtime(&now);
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
		return ;
	printf("[%s%02i:%02i:%02i%s] [%s%s%s] ", RED, local->tm_hour, local->tm_min,
		local->tm_sec, RESET, color, type, RESET);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\n");
}

char	*get_object_type_string(t_object_type type)
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
	char	*temp;

	temp = get_object_type_string(object_type);
	if (object_type == SPHERE)
		log_event(type, "%s%s", message, temp);
	else if (object_type == PLANE)
		log_event(type, "%s%s", message, temp);
	else if (object_type == CYLINDER)
		log_event(type, "%s%s", message, temp);
	else
		log_event(type, "%s%s", message, temp);
}
