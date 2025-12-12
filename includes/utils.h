/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:17:10 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 19:24:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* --- Mise en forme --- */
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

/* --- Couleurs Standard --- */
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

/* --- Couleurs Gras (Bold) --- */
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_MAGENTA "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define B_WHITE "\033[1;37m"

# define WHITESPACE_CHARS " \t\n\v\f\r"

# define ESCAPE_KEY 53
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define UP_ARROW_KEY 126
# define DOWN_ARROW_KEY 125

typedef int	t_status; // EXIT_SUCCESS or EXIT_FAILURE

void	print_usage(void);
void	log_info(const char *message);
void	log_detail(const char *message, const char *detail);
void	log_process(const char *message);

size_t	ft_strcspn(const char *str, const char *reject);
size_t	ft_strspn(const char *str, const char *accept);

void		destroy_scene(t_scene *scene);
t_status	clean_exit(t_scene *scene, t_status status);

#endif