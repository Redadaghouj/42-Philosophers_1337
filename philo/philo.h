/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:34 by reda              #+#    #+#             */
/*   Updated: 2025/05/04 23:18:03 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <strings.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define MS_TO_US 1000
# define MAX_PHILOS 200
# define MIN_PHILOS 1

typedef unsigned long	t_timestamp;

typedef struct s_data
{
	int				nbr_of_philos;
	int				all_eats;
	int				must_eats;
	bool			death_happened;
	t_timestamp		time_to_die;
	t_timestamp		time_to_eat;
	t_timestamp		time_to_sleep;
	t_timestamp		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				meals_count;
	t_data			*data;
	pthread_t		thread;
	t_timestamp		last_meal_time;
	bool			finished;
}				t_philo;

/* UTILS */
int			ft_strlen(const char *s);
int			ft_atoi(const char *nptr);

/* PARSING */
int			parse_and_validate_args(int argc, char *argv[]);

/* START SIMULATION */
int			start_simulation(t_philo *philo);

/* STOP SIMULATION */
int			check_death(t_philo *philo);
void		monitor_death(t_philo	*philo);
bool		get_is_dead(t_philo *philo);

/* LIFE_CYCLE */
void		pick_up_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		think(t_philo *philo);

/* PHILO UTILS */
t_timestamp	get_current_time(void);
void		ft_usleep(t_timestamp time, t_philo *philo);
void		print_state(t_philo *philo, char *state);
int			print_error(char *msg);
void		must_eats(t_philo *philo);

#endif