/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:03:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/29 21:21:14 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	pthread_mutex_lock(&philo->data->extra_layer);
	if (!philo->data->death_happened)
	{
		time = get_current_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->data->print);
		if (philo->meals_count < philo->data->must_eats)
			printf("%-5lu %-3d %s\n", time, philo->id, state);
		fflush(stdout); // -REMOVE-
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->extra_layer);
}

void	one_fork_available(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	usleep(philo->data->time_to_die * MS_TO_US);
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
		while (true)
		{
			pthread_mutex_lock(&philo->data->meal_mutex);
			pthread_mutex_lock(&philo->data->extra_layer);
			if (philo->data->death_happened)
			{
				pthread_mutex_unlock(&philo->data->extra_layer);
				pthread_mutex_unlock(&philo->data->meal_mutex);
				break ;
			}
			pthread_mutex_unlock(&philo->data->extra_layer);
			pthread_mutex_unlock(&philo->data->meal_mutex);
			pick_up_forks(philo);
			eat(philo);
			put_down_forks(philo);
			sleep_philo(philo);
			think(philo);
		}
	}
	return (NULL);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		i;
	int		nbr;

	philo = (t_philo *)arg;
	nbr = philo->data->nbr_of_philos;
	while (true)
	{
		i = 0;
		while (i < nbr)
		{
			if (check_death(&philo[i]))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	start_simulation(t_philo *philo)
{
	int			i;
	int			philos_nbr;
	pthread_t	thread;

	i = -1;
	philos_nbr = philo->data->nbr_of_philos;
	philo->data->start_time = get_current_time();
	while (++i < philos_nbr)
		philo[i].last_meal_time = philo->data->start_time;
	i = 0;
	while (i < philos_nbr)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: Failed to create threads.\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&thread, NULL, monitor_death, philo) != 0)
	{
		print_error("Error: Failed to create thread.\n");
		return (EXIT_FAILURE);
	}
	pthread_join(thread, NULL);
	i = 0;
	while (i < philos_nbr)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
