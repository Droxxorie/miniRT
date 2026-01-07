/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:35:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 12:18:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	print_render_log(const char *message)
{
	char	*log;
	
	log = ft_strjoin("\r\033[2K", (char *)message);
	ft_putstr_fd(log, STDOUT_FILENO);
	free(log);
}

void	print_usage(void)
{
	printf(BOLD "miniRT - A simple ray tracing program\n" RESET);
	printf("Usage: ./miniRT <scene_file.rt>\n");
	printf("Arguments:\n");
	printf("  <scene_file.rt>   ");
	printf("Path to the scene description file (.rt format)\n");
	printf("Example:\n");
	printf("  ./miniRT test_files/exemple.rt\n");
}

void	print_controls(void)
{
	ft_putstr_fd(B_YELLOW"", 1);
	ft_putstr_fd("\n╔══════════════════════════════════════════════════╗\n", 1);
	ft_putstr_fd("║                 miniRT CONTROLS                  ║\n", 1);
	ft_putstr_fd("╚══════════════════════════════════════════════════╝\n", 1);
	ft_putstr_fd("╔══════════════════════════════════════════════════╗\n", 1);
	ft_putstr_fd("║                                     - GENERAL -  ║\n", 1);
	ft_putstr_fd("║  [ESC]   Exit the program                        ║\n", 1);
	ft_putstr_fd("║  [TAB]   Switch between ROT & TRANS mode         ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                   - SELECTION -  ║\n", 1);
	ft_putstr_fd("║  [L / R Click]   Select Object / Camera          ║\n", 1);
	ft_putstr_fd("║  [L]             Select light source             ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                    - MOVEMENT -  ║\n", 1);
	ft_putstr_fd("║  [W / S]   Move Forward / Backward               ║\n", 1);
	ft_putstr_fd("║  [A / D]   Move Left / Right                     ║\n", 1);
	ft_putstr_fd("║  [Q / E]   Move Down / Up                        ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                - MODIFICATION -  ║\n", 1);
	ft_putstr_fd("║  [+ / -]             Resize Diameter             ║\n", 1);
	ft_putstr_fd("║  [SHIFT] + [+ / -]   Resize Height (Cylinder)    ║\n", 1);
	ft_putstr_fd("╚══════════════════════════════════════════════════╝\n", 1);
	ft_putstr_fd(RESET "\n", 1);
}
