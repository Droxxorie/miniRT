/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 22:20:39 by eraad            ###   ########.fr       */
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
}

void	log_camera_info(t_camera *camera)
{
	if (!camera)
		return ;
	log_event(stdout, "WARN", "------\n");
	log_event(stdout, "INFO", "Camera Info:\n");
	log_event(stdout, "INFO", "ID: %d\n", camera->id);
	log_event(stdout, "INFO", "FOV: %.2f\n", camera->fov);
	log_event(stdout, "INFO", "Pos: [%.2f, %.2f, %.2f]\n", camera->position.x,
		camera->position.y, camera->position.z);
	log_event(stdout, "INFO", "Dir: [%.2f, %.2f, %.2f]\n", camera->direction.x,
		camera->direction.y, camera->direction.z);
}

void	log_light_info(t_light *light)
{
	if (!light)
		return ;
	log_event(stdout, "WARN", "------\n");
	log_event(stdout, "INFO", "Light ID: %d\n", light->id);
	log_event(stdout, "INFO", "Type: %s\n", get_light_type_str(light->type));
	log_event(stdout, "INFO", "Pos: [%.2f, %.2f, %.2f]\n", light->position.x,
		light->position.y, light->position.z);
	if (light->type == LIGHT_SUN || light->type == LIGHT_SPOT)
		log_event(stdout, "INFO", "Dir: [%.2f, %.2f, %.2f]\n",
			light->direction.x, light->direction.y, light->direction.z);
	log_event(stdout, "INFO", "Brightness: %.2f\n", light->brightness);
	log_event(stdout, "INFO", "Color: R:%.0f G:%.0f B:%.0f\n", light->color.r
		* 255, light->color.g * 255, light->color.b * 255);
	if (light->active)
		log_event(stdout, "INFO", "Status: [ON]\n");
	else
		log_event(stdout, "INFO", "Status: [OFF]\n");
}

void	log_object_info(t_object *object)
{
	t_vec3	pos;
	t_vec3	scale;
	t_color	color;

	if (!object)
		return ;
	get_scale_and_position(object, &scale, &pos, &color);
	log_event(stdout, "WARN", "------\n");
	if (object->render_as_sdf == TRUE)
		log_event(stdout, "INFO", "Type: %s [SDF]\n",
			get_object_type_str(object->type));
	else
		log_event(stdout, "INFO", "Type: %s\n",
			get_object_type_str(object->type));
	log_event(stdout, "INFO", "Pos: [%.2f, %.2f, %.2f]\n", pos.x, pos.y, pos.z);
	log_event(stdout, "INFO", "Scale: [%.2f, %.2f, %.2f]\n", scale.x, scale.y,
		scale.z);
	log_event(stdout, "INFO", "Color: R:%.0f G:%.0f B:%.0f\n", color.r, color.g,
		color.b);
	if (object->material)
		log_event(stdout, "INFO", "Material: %s\n", object->material->name);
}
