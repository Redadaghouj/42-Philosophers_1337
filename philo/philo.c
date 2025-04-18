/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/18 00:10:04 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_routine(void *arg)
{
	printf("im a detached thread\n");
	return (NULL);
}

int	main(void)
{
	int i = 0;
	pthread_t thread;

	if (pthread_create(&thread, NULL, start_routine, NULL) != 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread);
	sleep(100);
	return (EXIT_SUCCESS);
}
