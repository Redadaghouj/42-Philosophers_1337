/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:03:09 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/29 17:44:04 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(t_timestamp time, t_philo *philo)
{
	t_timestamp		wake_up;
	unsigned int	must_eats;

	must_eats = philo->data->must_eats;
	wake_up = get_current_time() + time;
	while (get_current_time() < wake_up)
	{
		pthread_mutex_lock(&philo->data->extra_layer);
		if (philo->data->death_happened || philo->meals_count >= must_eats)
		{
			pthread_mutex_unlock(&philo->data->extra_layer);
			break ;
		}
		pthread_mutex_unlock(&philo->data->extra_layer);
		check_death(philo);
		usleep(100);
	}
}
