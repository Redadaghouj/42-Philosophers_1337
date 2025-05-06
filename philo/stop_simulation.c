/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:46:43 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/06 16:30:55 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_is_dead(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->mutex.death);
	is_dead = philo->data->death_happened;
	pthread_mutex_unlock(&philo->data->mutex.death);
	return (is_dead);
}

int	check_death(t_philo *philo)
{
	t_timestamp		inactive_time;
	int				eats;
	int				nbr_of_philos;

	pthread_mutex_lock(&philo->data->mutex.meal);
	eats = philo->data->all_eats;
	pthread_mutex_unlock(&philo->data->mutex.meal);
	nbr_of_philos = philo->data->nbr_of_philos;
	inactive_time = get_current_time() - philo->last_meal_time;
	if (inactive_time >= philo->data->time_to_die || eats == nbr_of_philos)
	{
		if (!get_is_dead(philo))
		{
			print_state(philo, "died");
			pthread_mutex_lock(&philo->data->mutex.death);
			philo->data->death_happened = true;
			pthread_mutex_unlock(&philo->data->mutex.death);
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
