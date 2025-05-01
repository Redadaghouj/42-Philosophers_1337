/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:51 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/01 20:17:45 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	bool			is_dead;
	int				eats;
	int				nbr_of_philos;

	sem_wait(philo->data->meal_sem);
	eats = philo->data->all_eats;
	nbr_of_philos = philo->data->nbr_of_philos;
	sem_post(philo->data->meal_sem);
	inactive_time = get_current_time() - philo->last_meal_time;
	is_dead = get_is_dead(philo);
	if (inactive_time >= philo->data->time_to_die || eats == nbr_of_philos)
	{
		if (!is_dead)
		{
			print_state(philo, "died");
			sem_wait(philo->data->death_sem);
			philo->data->death_happened = true;
			sem_post(philo->data->death_sem);
		}
	}
	is_dead = get_is_dead(philo);
	return (is_dead);
}

void	*monitor_death(void	*arg)
{
	t_philo	*philo;
	int		i;
	int		nbr;

	philo = (t_philo *) arg;
	nbr = philo->data->nbr_of_philos;
	while (true)
	{
		i = 0;
		while (i < nbr)
		{
			if (check_death(&philo[i]))
				return ;
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	has_died(t_philo *philo)
{
	bool	is_dead;

	is_dead = get_is_dead(philo);
	if (is_dead)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_monitor_thread(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_death, philo) != 0)
	{
		print_error("Error: Failed to create thread.\n");
		return (EXIT_FAILURE);
	}
	pthread_join(thread, NULL);
	return (EXIT_SUCCESS);
}