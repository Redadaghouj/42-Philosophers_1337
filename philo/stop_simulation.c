/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:46:43 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/06 12:06:38 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int				eats;
	int				nbr_of_philos;

	pthread_mutex_lock(&philo->data->meal_mutex);
	eats = philo->data->all_eats;
	nbr_of_philos = philo->data->nbr_of_philos;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	inactive_time = get_current_time() - philo->last_meal_time;
	if (inactive_time >= philo->data->time_to_die || eats == nbr_of_philos)
	{
		if (!get_is_dead(philo))
		{
			print_state(philo, "died");
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->death_mutex);
		}
	}
	return (get_is_dead(philo));
}

void	monitor_death(t_philo	*philo)
{
	int		i;

	while (true)
	{
		i = 0;
		while (i < philo->data->nbr_of_philos)
		{
			if (check_death(&philo[i]))
				return ;
			i++;
		}
		usleep(500);
	}
}
