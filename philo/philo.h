/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:34 by reda              #+#    #+#             */
/*   Updated: 2025/04/25 21:28:45 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <strings.h>
# include <stdio.h> // -REMOVE-
# include <unistd.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define MAX_PHILOS 200
# define MIN_PHILOS 1

typedef struct s_data
{
	int				nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eats;
	bool			death_happened;
}				t_data;

typedef struct s_philo
{
	int				id;
	unsigned int	last_meal_time;
	unsigned int	meals_count;
	t_data			*data;
}				t_philo;

/* UTILS */
int	ft_strlen(const char *s);
int	ft_atoi(const char *nptr);

/* ERROR HANDLERS */
int	print_error(char *msg);

/* PARSING */
int	parse_and_validate_args(int argc, char *argv[]);

#endif