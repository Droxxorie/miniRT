/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_loc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:52:18 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 15:55:50 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
		ft_putstr_fd(B_YELLOW "^ HERE\n" RESET, STDERR_FILENO);
	}
}

void	print_error_loc(t_scene *scene, char *current_pos, char *message)
{
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd(" (Line ", STDERR_FILENO);
		ft_putnbr_fd(scene->line_number, STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
	}
	print_line_context(scene, current_pos);
}

void	print_error_limit(t_scene *scene, char *start_ptr, char *entity_name,
		int limit)
{
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	ft_putstr_fd("Maximum number of ", STDERR_FILENO);
	if (entity_name)
		ft_putstr_fd(entity_name, STDERR_FILENO);
	ft_putstr_fd(" exceeded (Limit: ", STDERR_FILENO);
	ft_putnbr_fd(limit, STDERR_FILENO);
	ft_putstr_fd(") (Line ", STDERR_FILENO);
	ft_putnbr_fd(scene->line_number, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	print_line_context(scene, start_ptr);
}
