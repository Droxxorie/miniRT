/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 03:09:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	log_event(FILE *stream, char *type, char *format, ...)
{
	va_list		args;
	time_t		now;
	struct tm	*local;
	char		*color;

	now = time(NULL);
	local = localtime(&now);
	if (ft_strncmp(type, "ERROR", 5) == 0)
		color = R;
	else if (ft_strncmp(type, "SUCCESS", 7) == 0)
		color = G;
	else if (ft_strncmp(type, "PERF", 4) == 0)
		color = MAGENTA;
	else if (ft_strncmp(type, "WARN", 4) == 0)
		color = Y;
	else if (ft_strncmp(type, "INFO", 4) == 0)
		color = B_B;
	else
		return ;
	fprintf((FILE *)stream, "[%s%02i:%02i:%02i%s] [%s%s%s] ", R, local->tm_hour,
		local->tm_min, local->tm_sec, RESET, color, type, RESET);
	va_start(args, format);
	vfprintf((FILE *)stream, format, args);
	va_end(args);
	fprintf((FILE *)stream, "\n");
}

char	*get_object_type_string(t_object_type type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else if (type == RECTANGLE)
		return ("RECTANGLE");
	else if (type == DISK)
		return ("DISK");
	else if (type == TRIANGLE)
		return ("TRIANGLE");
	else if (type == TORUS)
		return ("TORUS");
	else if (type == CONE)
		return ("CONE");
	else if (type == BOX)
		return ("BOX");
	else
		return ("NONE");
}

void	log_event_object(char *type, char *message, t_object_type object_type)
{
	char	*temp;

	temp = get_object_type_string(object_type);
	log_event(stdout, type, "%s%s", message, temp);
}
