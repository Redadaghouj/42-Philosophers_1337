/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:51 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/30 18:00:52 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	get_is_dead(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	is_dead = philo->data->death_happened;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (is_dead);
}

int	check_death(t_philo *philo)
{
	t_timestamp		inactive_time;
	bool			is_dead;
	int				eats;
	int				nbr_of_philos;

	pthread_mutex_lock(&philo->data->meal_mutex);
	eats = philo->data->all_eats;
	nbr_of_philos = philo->data->nbr_of_philos;
	inactive_time = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	is_dead = get_is_dead(philo);
	if (inactive_time >= philo->data->time_to_die || eats == nbr_of_philos)
	{
		if (!is_dead)
		{
			print_state(philo, "died");
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->death_mutex);
		}
	}
	is_dead = get_is_dead(philo);
	return (is_dead);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		i;
	int		nbr;

	philo = (t_philo *)arg;
	nbr = philo->data->nbr_of_philos;
	while (true)
	{
		i = 0;
		while (i < nbr)
		{
			if (check_death(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
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
