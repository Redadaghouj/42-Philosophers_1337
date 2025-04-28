/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:42:28 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/28 19:42:29 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	philo->meals_count++;
	philo->last_meal_time = get_current_time();
	ft_usleep(philo->data->time_to_eat, philo);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
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
