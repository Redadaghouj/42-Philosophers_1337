/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:51 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/14 17:10:50 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	reap_and_kill_children(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->data->must_eats != -1)
	{
		while (++i < philo->data->nbr_of_philos)
			sem_wait(philo->data->sem.eats_sem);
	}
	else
		waitpid(-1, NULL, 0);
	i = -1;
	while (++i < philo->data->nbr_of_philos)
		kill(philo->data->pids[i], SIGKILL);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

bool	get_is_dead(t_philo *philo)
{
	bool	is_dead;

	sem_wait(philo->data->sem.death_sem);
	is_dead = philo->data->death_happened;
	sem_post(philo->data->sem.death_sem);
	return (is_dead);
}

void	check_death(t_philo *philo)
{
	t_timestamp		inactive_time;

	sem_wait(philo->data->sem.meal_sem);
	inactive_time = get_current_time() - philo->last_meal_time;
	sem_post(philo->data->sem.meal_sem);
	if (inactive_time >= philo->data->time_to_die)
	{
		post_eats_sem(philo);
		if (!get_is_dead(philo))
		{
			print_state(philo, "died");
			sem_wait(philo->data->sem.death_sem);
			philo->data->death_happened = true;
			sem_post(philo->data->sem.death_sem);
			ft_close_sem(philo);
			exit(EXIT_SUCCESS);
		}
	}
}

void	*monitor_death(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (true)
	{
		check_death(philo);
		usleep(100);
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
