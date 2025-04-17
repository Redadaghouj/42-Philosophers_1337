/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/17 22:18:33 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define MAX_SIZE 1000
pthread_mutex_t mutex;
int stack[MAX_SIZE];
int top = -1;

// void	print_stack()
// {
// 	int i = 0;

// 	while (i < MAX_SIZE && top >= 0)
// 	{
// 		printf("%d ", stack[i]);
// 		i++;
// 	}
// 	if (top < 0)
// 		printf("Stack is empty\n");
// }

// void	push(int value)
// {
// 	pthread_mutex_lock(&mutex);
// 	top++;
// 	stack[top] = value;
// 	pthread_mutex_unlock(&mutex);
// }

// int pop()
// {
// 	pthread_mutex_lock(&mutex);
// 	if (top < 0)
// 	{
// 		pthread_mutex_unlock(&mutex);
// 		return (-1);
// 	}
// 	int val = stack[top];
// 	top--;
// 	pthread_mutex_unlock(&mutex);
// 	return (val);
// }

// void	*start_routine(void *arg)
// {
// 	int i = 0;

// 	while (i < (MAX_SIZE / 2))
// 	{
// 		push(i + 1);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < (MAX_SIZE / 2))
// 	{
// 		pop();
// 		i++;
// 	}
// 	return (NULL);
// }

void	print_stack()
{
	int i = 0;

	while (i < MAX_SIZE && top >= 0)
	{
		printf("%d ", stack[i]);
		i++;
	}
	if (top < 0)
		printf("Stack is empty\n");
}

void	push(int value)
{
	top++;
	stack[top] = value;
}

int pop()
{
	if (top < 0)
		return (-1);
	int val = stack[top];
	top--;
	return (val);
}

void	*start_routine(void *arg)
{
	int i = 0;

		pthread_mutex_lock(&mutex);
	while (i < (MAX_SIZE / 2))
	{
		push(i + 1);
		i++;
		// pthread_mutex_unlock(&mutex);
	}
	// i = 0;
	// while (i < (MAX_SIZE / 2))
	// {
	// 	// pthread_mutex_lock(&mutex);
	// 	pop();
	// 	i++;
	// }
		pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	int i = 0;
	pthread_t thread[2];

	pthread_mutex_init(&mutex, NULL);
	while (i < 2)
	{
		if (pthread_create(&thread[i], NULL, start_routine, NULL) != 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_mutex_destroy(&mutex);
	print_stack();
	return (EXIT_SUCCESS);
}
