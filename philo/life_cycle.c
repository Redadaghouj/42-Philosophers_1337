/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:44:05 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/06 16:30:55 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->mutex.forks[first]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->mutex.forks[second]);
	print_state(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->data->mutex.meal);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->mutex.meal);
	ft_usleep(philo->data->time_to_eat, philo);
	must_eats(philo);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex.forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex.forks[philo->left_fork]);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
