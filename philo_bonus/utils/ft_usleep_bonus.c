/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:42:13 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/29 10:25:25 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
			check_death(philo);
			usleep(100);
			continue ;
		}
		pthread_mutex_unlock(&philo->data->layer);
		break ;
	}
}
