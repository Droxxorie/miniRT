/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:35:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 21:57:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_usage(void)
{
	printf(BOLD "miniRT - A simple ray tracing program\n" RESET);
	printf("Usage: ./miniRT <scene_file.rt>\n");
	printf("Arguments:\n");
	printf("  <scene_file.rt>   ");
	printf("Path to the scene description file (.rt format)\n");
	printf("Example:\n");
	printf("  ./miniRT test_files/exemple.rt\n");
	exit(EXIT_SUCCESS);
}

void	print_object_details(t_object_type type)
{
	if (type == SPHERE)
		ft_putstr_fd("Object Type: SPHERE\n", 1);
	else if (type == PLANE)
		ft_putstr_fd("Object Type: PLANE\n", 1);
	else if (type == CYLINDER)
		ft_putstr_fd("Object Type: CYLINDER\n", 1);
	else
		ft_putstr_fd("Object Type: NONE\n", 1);
}
