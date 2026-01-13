/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enter_key_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:40:30 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 13:48:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_enter_key(t_scene *scene)
{
	char		filename[64];
	time_t		now;
	struct tm	*t;

	if (scene->to_save)
	{
		log_event(stdout, "WARN", "Already in save mode, ignoring ENTER key\n");
		return ;
	}
	now = time(NULL);
	t = localtime(&now);
	sprintf(filename, "output/%d%02d%02d_%02d%02d%02d.bmp", t->tm_year + 1900,
		t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	scene->save_file = filename;
	if (mkdir("output", 0755) == 0)
	{
		log_event(stdout, "WARN", "'output' directory do not exist\n");
		log_event(stdout, "INFO",
			"Created 'output' directory for output files\n");
	}
	save_image_to_bmp(scene);
	scene->save_file = NULL;
}
