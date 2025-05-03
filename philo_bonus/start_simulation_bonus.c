/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/02 12:27:06 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_fork_available(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
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
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->data->nbr_of_philos > 1)
		create_monitor_thread(philo);
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
}

int	fork_processes(t_philo *philo, int philos_nbr)
{
	t_data	*data;
	int		i;

	data = philo->data;
	i = -1;
	while (++i < philos_nbr)
	{
		data->pids[i] = ft_fork();
		if (data->pids[i] == 0)
			routine(philo);
	}
	while (wait(NULL) != -1)
	{
		i = -1;
		while (++i < data->nbr_of_philos)
			kill(data->pids[i], SIGKILL);
		puts("DONE!");
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	start_simulation(t_philo *philo)
{
	int		i;
	int		philos_nbr;

	i = -1;
	philos_nbr = philo->data->nbr_of_philos;
	philo->data->start_time = get_current_time();
	while (++i < philos_nbr)
		philo[i].last_meal_time = philo->data->start_time;
	if (fork_processes(philo, philos_nbr))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
