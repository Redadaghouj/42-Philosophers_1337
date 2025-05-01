/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/01 13:27:54 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	*one_fork_available(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
// 	print_state(philo, "has taken a fork");
// 	ft_usleep(philo->data->time_to_die, philo);
// 	print_state(philo, "died");
// 	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
// 	return (NULL);
// }

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->data->nbr_of_philos == 1)
	// 	return (one_fork_available(philo));
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

int	fork_processes(t_philo *philo, int philos_nbr)
{
	int			i;

	i = -1;
	while (++i < philos_nbr)
	{
		
	}
	if (philos_nbr > 1)
		monitor_death(philo);
	i = -1;
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
	if (fork_processes(philo, philos_nbr))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
