/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:43:33 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/28 21:48:36 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_timestamp	get_current_time(void)
{
	struct timeval	tv;
	t_timestamp		miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

void	print_state(t_philo *philo, char *state)
{
	t_timestamp	time;

	pthread_mutex_lock(&philo->data->layer);
	if (!philo->data->death_happened)
	{
		time = get_current_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->print);
		if (philo->meals_count < philo->data->must_eats)
			printf("%-5ld %-3d %s\n", time, philo->id, state);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->layer);
}

void	one_fork_available(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	usleep(philo->data->time_to_die);
	print_state(philo, "died");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_of_philos == 1)
		one_fork_available(philo);
	else
	{
		if (philo->id % 2 == 0)
			usleep(500);
		while (1)
		{
			if (check_must_eats(philo))
				break ;
			pick_up_forks(philo);
			eat(philo);
			put_down_forks(philo);
			sleep_philo(philo);
			think(philo);
		}
	}
	return (NULL);
}

int	start_simulation(t_philo *philo)
{
	int	i;
	int	philos_nbr;

	i = 0;
	philos_nbr = philo->data->nbr_of_philos;
	philo->data->start_time = get_current_time();
	while (i < philos_nbr)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: Failed to create threads.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < philos_nbr)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
