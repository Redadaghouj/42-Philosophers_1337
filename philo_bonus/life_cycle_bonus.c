/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:59:17 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/05 21:16:44 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_up_forks(t_philo *philo)
{
	sem_wait(philo->data->sem.forks_sem);
	print_state(philo, "has taken a fork");
	sem_wait(philo->data->sem.forks_sem);
	print_state(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	print_state(philo, "is eating");
	sem_wait(philo->data->sem.meal_sem);
	philo->last_meal_time = get_current_time();
	sem_post(philo->data->sem.meal_sem);
	ft_usleep(philo->data->time_to_eat, philo);
	must_eats(philo);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->sem.forks_sem);
	sem_post(philo->data->sem.forks_sem);
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
