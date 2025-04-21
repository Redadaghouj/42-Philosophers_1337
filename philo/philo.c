/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/21 22:58:40 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*sem;

void	*routine(void *arg)
{
	int	id;

	id = *(int *)arg;
	sem_wait(sem);
	printf("Thread %d: Working...\n", id);
	sleep(1);
	sem_post(sem);
	printf("Thread %d: Done.\n", id);
	return (NULL);
}

void	error_exit()
{
	perror("Error");
	sem_close(sem);
	sem_unlink("/my_sem");
	exit(EXIT_FAILURE);
}

int	main(void)
{
	pthread_t	thread[THREAD_NUM];
	int			ids[THREAD_NUM];
	int			i;

	sem = sem_open("/my_sem", O_CREAT | O_EXCL, 0666, 3);
	if (sem == SEM_FAILED)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		i = 0;
		while (i < THREAD_NUM)
		{
			ids[i] = i + 1;
			if (pthread_create(&thread[i], NULL, routine, &ids[i]) != 0)
				error_exit();
			i++;
		}
		i = 0;
		while (i < THREAD_NUM)
		{
			pthread_join(thread[i], NULL);
			i++;
		}
		sem_close(sem);
		sem_unlink("/my_sem");
	}
	return (EXIT_SUCCESS);
}
