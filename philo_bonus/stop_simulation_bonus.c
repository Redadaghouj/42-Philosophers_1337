/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:51 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/05 11:06:23 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	reap_and_kill_children(t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (wait(&status) != -1)
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
		{
			while (++i < philo->data->nbr_of_philos)
				kill(philo->data->pids[i], SIGKILL);
		}
	}
}

bool	get_is_dead(t_philo *philo)
{
	bool	is_dead;

	sem_wait(philo->data->death_sem);
	is_dead = philo->data->death_happened;
	sem_post(philo->data->death_sem);
	return (is_dead);
}

int	check_death(t_philo *philo)
{
	t_timestamp		inactive_time;
	int				eats;
	int				nbr_of_philos;

	sem_wait(philo->data->meal_sem);
	eats = philo->data->all_eats;
	nbr_of_philos = philo->data->nbr_of_philos;
	sem_post(philo->data->meal_sem);
	inactive_time = get_current_time() - philo->last_meal_time;
	if (inactive_time >= philo->data->time_to_die || eats == nbr_of_philos)
	{
		if (!get_is_dead(philo))
		{
			if (philo->data->must_eats == -1)
				print_state(philo, "died");
			sem_wait(philo->data->death_sem);
			philo->data->death_happened = true;
			sem_post(philo->data->death_sem);
		}
	}
	return (get_is_dead(philo));
}

void	*monitor_death(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (true)
	{
		if (check_death(philo))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	create_monitor_thread(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_death, philo) != 0)
	{
		print_error("Error: Failed to create thread.\n");
		return (EXIT_FAILURE);
	}
	pthread_detach(thread);
	return (EXIT_SUCCESS);
}
