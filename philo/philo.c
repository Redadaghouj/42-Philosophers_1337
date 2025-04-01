/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/01 16:05:51 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void* arg) {
	int id = *(int*)arg;
	printf("Thread %d starting\n", id);
	sleep(1);
	printf("Thread %d ending\n", id);
	return NULL;
}

int	main(void) {
	pthread_t thread1, thread2;
	int id1 = 1, id2 = 2;
	
	pthread_create(&thread1, NULL, thread_function, &id1);
	pthread_create(&thread2, NULL, thread_function, &id2);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("All threads completed\n");
	return (0);
}
