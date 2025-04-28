/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:03:09 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/28 18:41:17 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(t_timestamp time, t_philo *philo)
{
	t_timestamp		wake_up;
	unsigned int	must_eats;

	must_eats = philo->data->must_eats;
	wake_up = (get_current_time() * MS_TO_US) + time;
	while ((get_current_time() * MS_TO_US) < wake_up)
	{
		pthread_mutex_lock(&philo->data->layer);
		if (!philo->data->death_happened || philo->meals_count <= must_eats)
		{
			pthread_mutex_unlock(&philo->data->layer);
			usleep(100);
			continue ;
		}
		pthread_mutex_unlock(&philo->data->layer);
		break ;
	}
}
