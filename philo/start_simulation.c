/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:03:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/06 16:29:49 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_fork_available(t_philo *philo)
{
	think(philo);
	pthread_mutex_lock(&philo->data->mutex.forks[philo->right_fork]);
	print_state(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	print_state(philo, "died");
	pthread_mutex_unlock(&philo->data->mutex.forks[philo->right_fork]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_of_philos == 1)
		return (one_fork_available(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_is_dead(philo))
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo *philo)
{
	int	i;

	i = -1;
	philo->data->start_time = get_current_time();
	while (++i < philo->data->nbr_of_philos)
	{
		philo[i].last_meal_time = philo->data->start_time;
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: Failed to create threads.\n");
			return (EXIT_FAILURE);
		}
	}
	if (philo->data->nbr_of_philos > 1)
		monitor_death(philo);
	i = -1;
	while (++i < philo->data->nbr_of_philos)
		pthread_join(philo[i].thread, NULL);
	return (EXIT_SUCCESS);
}
