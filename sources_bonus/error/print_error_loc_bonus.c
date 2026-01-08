/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_loc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:52:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 16:25:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	print_line_context(t_scene *scene, char *pos)
{
	int	offset;

	if (!scene->line_ptr)
		return ;
	ft_putstr_fd("\t", STDERR_FILENO);
	ft_putstr_fd(scene->line_ptr, STDERR_FILENO);
	if (scene->line_ptr[ft_strlen(scene->line_ptr) - 1] != '\n')
		ft_putstr_fd("\n", STDERR_FILENO);
	if (pos >= scene->line_ptr)
	{
		offset = pos - scene->line_ptr;
		ft_putstr_fd("\t", STDERR_FILENO);
		while (offset-- > 0)
			ft_putstr_fd(" ", STDERR_FILENO);
		ft_putstr_fd(B_R "^ HERE\n" RESET, STDERR_FILENO);
	}
}

void	print_error_loc(t_scene *scene, char *current_pos, char *message)
{
	char	buffer[256];

	sprintf(buffer, "%s (Line %d)", message, scene->line_number);
	log_event(stderr, "ERROR", buffer);
	print_line_context(scene, current_pos);
}

void	print_error_limit(t_scene *scene, char *start_ptr, char *entity_name,
		int limit)
{
	char	buffer[256];

	sprintf(buffer, "Maximum number of %s exceeded (Limit: %d) (Line %d)",
		entity_name, limit, scene->line_number);
	log_event(stderr, "ERROR", buffer);
	print_line_context(scene, start_ptr);
}
