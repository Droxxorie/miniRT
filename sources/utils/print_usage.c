/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:10:24 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 16:14:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_usage(void)
{
	printf(B_GREEN "miniRT - A simple ray tracing program\n" RESET);
	printf("Usage: ./miniRT <scene_file.rt>\n\n");
	printf("Arguments:\n");
	printf("  <scene_file.rt>   Path to the scene description file (.rt format)\n");
	printf("Example:\n");
	printf("  ./miniRT scenes/sample.rt\n");
	exit(EXIT_SUCCESS);
}
