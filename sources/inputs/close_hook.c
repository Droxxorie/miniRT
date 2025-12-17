/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:15:01 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 23:03:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	close_window(t_scene *scene)
{
	ft_putendl_fd("", STDOUT_FILENO);
	clean_exit(scene, EXIT_SUCCESS);
	return (0);
}
