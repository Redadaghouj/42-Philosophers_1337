/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:46:43 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/29 21:11:53 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_timestamp	inactive_time;
	bool		is_dead;

	pthread_mutex_lock(&philo->data->meal_mutex);
	inactive_time = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (inactive_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death);
		if (!philo->data->death_happened)
		{
			print_state(philo, "died");
			pthread_mutex_lock(&philo->data->extra_layer);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->extra_layer);
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	pthread_mutex_lock(&philo->data->extra_layer);
	is_dead = philo->data->death_happened;
	pthread_mutex_unlock(&philo->data->extra_layer);
	return (is_dead);
}

void	check_must_eats(t_philo *philo)
{
	unsigned long	must_eats;

	philo->meals_count++;
	must_eats = philo->data->must_eats;
	if (philo->meals_count >= must_eats && !philo->finished)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->data->all_eats++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		philo->finished = true;
	}
}
// void	set_death_flag(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->death);
//     if (!philo->data->death_happened)
//     {
//         pthread_mutex_lock(&philo->data->extra_layer);
//         philo->data->death_happened = true;
//         pthread_mutex_unlock(&philo->data->extra_layer);
//     }
//     pthread_mutex_unlock(&philo->data->death);
// }
