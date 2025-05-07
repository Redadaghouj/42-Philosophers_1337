/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:55:36 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/07 09:55:54 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo **philo)
{
	int	i;

	i = 0;
	if (*philo)
	{
		while (i < (*philo)->data->nbr_of_philos)
		{
			pthread_mutex_destroy(&(*philo)->data->mutex.forks[i]);
			i++;
		}
		pthread_mutex_destroy(&(*philo)->data->mutex.print);
		pthread_mutex_destroy(&(*philo)->data->mutex.death);
		pthread_mutex_destroy(&(*philo)->data->mutex.meal);
		free((*philo)->data->mutex.forks);
		free(*philo);
		*philo = NULL;
	}
}
