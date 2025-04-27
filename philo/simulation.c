/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:03:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/27 13:24:06 by mdaghouj         ###   ########.fr       */
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

	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d %s \n", time, philo->id, state);
	fflush(stdout);
	pthread_mutex_unlock(&philo->data->print);
}

void	check_death(t_philo *philo)
{
	t_timestamp	inactive_time;

	inactive_time = get_current_time() - philo->last_meal_time;
	// printf("philo %d - inactive time = %d\n", philo->id, inactive_time);
	pthread_mutex_lock(&philo->data->death);
	if (inactive_time >= philo->data->time_to_die && philo->last_meal_time != 0)
	{
		philo->data->death_happened = true;
		print_state(philo, "died");
	}
	pthread_mutex_unlock(&philo->data->death);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		check_death(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo *philo)
{
	int			i;
	int			philos_nbr;

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
//	5				200			200			200
/*
	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died
*/

/*
	while no philosopher has died:
		think()
		attempt_to_pick_up_forks()
		eat() [update last_meal_time and meal_count]
		put_down_forks()
		sleep()
*/