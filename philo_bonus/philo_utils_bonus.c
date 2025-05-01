/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:29 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/01 18:29:10 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(char *msg)
{
	int	len;

	len = ft_strlen(msg) + 1;
	write(STDERR_FILENO, msg, len);
	return (len);
}

t_timestamp	get_current_time(void)
{
	struct timeval	tv;
	t_timestamp		miliseconds;

	gettimeofday(&tv, NULL);
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

void	ft_usleep(t_timestamp time, t_philo *philo)
{
	t_timestamp		wake_up;
	unsigned int	must_eats;
	bool			is_dead;

	must_eats = philo->data->must_eats;
	wake_up = get_current_time() + time;
	while (get_current_time() < wake_up)
	{
		is_dead = get_is_dead(philo);
		if (is_dead)
			break ;
		check_death(philo);
		usleep(100);
	}
}

void	print_state(t_philo *philo, char *state)
{
	t_timestamp	time;
	bool		is_dead;

	is_dead = get_is_dead(philo);
	if (!is_dead)
	{
		time = get_current_time() - philo->data->start_time;
		sem_wait(philo->data->print_sem);
		if (!philo->data->death_happened)
			printf("%-5lu %-3d %s\n", time, philo->id, state);
		sem_post(philo->data->print_sem);
	}
}

void	must_eats(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->meal_mutex);
	// if (philo->data->must_eats > -1)
	// {
	// 	philo->meals_count++;
	// 	if (philo->meals_count >= philo->data->must_eats && !philo->finished)
	// 	{
	// 		philo->data->all_eats++;
	// 		philo->finished = true;
	// 	}
	// }
	// pthread_mutex_unlock(&philo->data->meal_mutex);
}
