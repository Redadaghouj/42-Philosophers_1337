/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:44:05 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/27 13:51:42 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
	usleep(philo->data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
