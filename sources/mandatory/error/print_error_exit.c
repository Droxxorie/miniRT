/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:24:58 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 20:11:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	sys_print_error_exit(const char *error_message)
{
	sys_print_error(error_message);
	exit(EXIT_FAILURE);
}

void	print_error_exit(const char *error_message)
{
	print_error(error_message);
	exit(EXIT_FAILURE);
}
