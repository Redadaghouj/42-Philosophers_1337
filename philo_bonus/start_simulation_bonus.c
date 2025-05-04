/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/05 00:21:18 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_fork_available(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	print_state(philo, "died");
	sem_post(philo->data->forks_sem);
	exit(EXIT_SUCCESS);
}

void	routine(t_philo	*philo)
{
	if (philo->data->nbr_of_philos == 1)
		one_fork_available(philo);
	// if (philo->id % 2 == 0)
	// 	usleep(500);
	// if (philo->data->nbr_of_philos > 1)
	// 	create_monitor_thread(philo);
	while (!get_is_dead(philo))
	{
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		think(philo);
		if (philo->finished)
			exit(EXIT_FULL_EAT);
	}
	exit(EXIT_SUCCESS);
}

int	start_simulation(t_philo *philo)
{
	int	i;
	int	status;

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
			puts("---Fork failed---\n");
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	while (wait(&status) != -1)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
		{
			while (++i < philo->data->nbr_of_philos)
				kill(philo->data->pids[i], SIGKILL);
		}
	}
	while (wait(NULL) != -1)
		;
	return (EXIT_SUCCESS);
}
