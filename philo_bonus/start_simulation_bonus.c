/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/14 21:23:36 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_fork_available(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	print_state(philo, "died");
	sem_post(philo->data->sem.forks_sem);
	exit(EXIT_SUCCESS);
}

void	routine(t_philo	*philo)
{
	if (philo->data->nbr_of_philos == 1)
		one_fork_available(philo);
	if (philo->data->nbr_of_philos > 1)
		create_monitor_thread(philo);
	while (!get_is_dead(philo))
	{
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	exit(EXIT_SUCCESS);
}

int	start_simulation(t_philo *philo)
{
	int	i;

	i = -1;
	philo->data->start_time = get_current_time();
	while (++i < philo->data->nbr_of_philos)
	{
		philo[i].last_meal_time = philo->data->start_time;
		philo->data->pids[i] = fork();
		if (philo->data->pids[i] == 0)
			routine(&philo[i]);
		else if (philo->data->pids[i] < 0)
		{
			print_error("Error: Fork failed\n");
			return (EXIT_FAILURE);
		}
	}
	reap_and_kill_children(philo);
	return (EXIT_SUCCESS);
}
