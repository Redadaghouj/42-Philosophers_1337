/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:29 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/09 18:39:57 by reda             ###   ########.fr       */
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

	wake_up = get_current_time() + time;
	while (get_current_time() < wake_up)
	{
		if (get_is_dead(philo))
			break ;
		usleep(100);
	}
}

void	print_state(t_philo *philo, char *state)
{
	if (!get_is_dead(philo))
	{
		sem_wait(philo->data->sem.print_sem);
		if (!get_is_dead(philo))
			printf("%-4lu %-3d %s\n", get_current_time()
				- philo->data->start_time, philo->id, state);
		if (ft_strcmp(state, "died") != 0)
			sem_post(philo->data->sem.print_sem);
	}
}

void	must_eats(t_philo *philo)
{
	sem_wait(philo->data->sem.meal_sem);
	if (philo->data->must_eats > -1)
	{
		philo->meals_count++;
		if (philo->meals_count >= philo->data->must_eats && !philo->finished)
		{
			philo->finished = true;
			sem_post(philo->data->sem.eats_sem);
		}
	}
	sem_post(philo->data->sem.meal_sem);
}
