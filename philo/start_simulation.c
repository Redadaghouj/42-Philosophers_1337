/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:03:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/30 20:58:31 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		one_fork_available(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(500);
	while (true)
	{
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		think(philo);
		if (has_died(philo))
			break ;
	}
	return (NULL);
}

int	create_threads(t_philo *philo, int philos_nbr)
{
	int			i;

	i = -1;
	while (++i < philos_nbr)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			print_error("Error: Failed to create threads.\n");
			return (EXIT_FAILURE);
		}
	}
	if (philos_nbr > 1)
		monitor_death(philo);
	i = -1;
	while (++i < philos_nbr)
		pthread_join(philo[i].thread, NULL);
	return (EXIT_SUCCESS);
}

int	start_simulation(t_philo *philo)
{
	int			i;
	int			philos_nbr;

	i = -1;
	philos_nbr = philo->data->nbr_of_philos;
	philo->data->start_time = get_current_time();
	while (++i < philos_nbr)
		philo[i].last_meal_time = philo->data->start_time;
	if (create_threads(philo, philos_nbr))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
