/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:46:43 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/28 18:34:21 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_timestamp	inactive_time;
	bool		is_dead;

	inactive_time = get_current_time() - philo->last_meal_time;
	if (inactive_time >= philo->data->time_to_die && philo->last_meal_time != 0)
	{
		pthread_mutex_lock(&philo->data->death);
		if (!philo->data->death_happened)
		{
			print_state(philo, "died");
			pthread_mutex_lock(&philo->data->layer);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->layer);
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	pthread_mutex_lock(&philo->data->layer);
	is_dead = philo->data->death_happened;
	pthread_mutex_unlock(&philo->data->layer);
	return (is_dead);
}

int	check_must_eats(t_philo *philo)
{
	int		must_eats;
	bool	is_dead;

	must_eats = philo->data->must_eats;
	if (philo->meals_count == must_eats)
	{
		pthread_mutex_lock(&philo->data->death);
		if (!philo->data->death_happened)
		{
			pthread_mutex_lock(&philo->data->layer);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->layer);
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	pthread_mutex_lock(&philo->data->layer);
	is_dead = philo->data->death_happened;
	pthread_mutex_unlock(&philo->data->layer);
	return (is_dead);
}
