/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/14 21:16:57 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define MS_TO_US 1000
# define MAX_PHILOS 200
# define MIN_PHILOS 1
# define FORKS_SEM "/forks_sem"
# define PRINT_SEM "/print_sem"
# define DEATH_SEM "/death_sem"
# define MEAL_SEM "/meal_sem"
# define EATS_SEM "/eats_sem"

typedef unsigned long	t_timestamp;

typedef struct s_sem
{
	sem_t		*print_sem;
	sem_t		*forks_sem;
	sem_t		*death_sem;
	sem_t		*meal_sem;
	sem_t		*eats_sem;
}				t_sem;

typedef struct s_data
{
	int			nbr_of_philos;
	int			must_eats;
	bool		death_happened;
	t_timestamp	time_to_die;
	t_timestamp	time_to_eat;
	t_timestamp	time_to_sleep;
	t_timestamp	start_time;
	t_sem		sem;
	pid_t		*pids;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				meals_count;
	t_data			*data;
	t_timestamp		last_meal_time;
	bool			finished;
}				t_philo;

/* UTILS BONUS */
int			ft_strlen(const char *s);
int			ft_atoi(const char *nptr);
int			ft_strcmp(char *s1, char *s2);

/* PARSING BONUS */
int			parse_and_validate_args(int argc, char *argv[]);

/* START SIMULATION BONUS */
int			start_simulation(t_philo *philo);

/* STOP SIMULATION BONUS */
void		check_death(t_philo *philo);
void		*monitor_death(void	*arg);
bool		get_is_dead(t_philo *philo);
int			create_monitor_thread(t_philo *philo);
void		reap_and_kill_children(t_philo *philo);

/* LIFE_CYCLE BONUS */
void		pick_up_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		think(t_philo *philo);

/* PHILO UTILS BONUS */
t_timestamp	get_current_time(void);
void		ft_usleep(t_timestamp time, t_philo *philo);
void		print_state(t_philo *philo, char *state);
int			print_error(char *msg);
void		must_eats(t_philo *philo);

/* CLEANUP */
void		cleanup(t_philo **philo);
void		ft_unlink_sem(void);
void		post_eats_sem(t_philo *philo);
void		ft_close_sem(t_philo *philo);

#endif