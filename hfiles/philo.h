/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:58:17 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/09 13:00:11 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_data
{
	long int		st_time;
	int				nb_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				nb_meals_max;
	int				dead;
	pthread_mutex_t	mdead;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}				t_data;

typedef struct s_philo
{
	int					id;
	int					status;
	int					nb_meals;
	long int			last_meal;
	pthread_t			*thread;
	t_data				*data;
}				t_philo;

void			free_all(t_philo **philo, t_data *data);
void			ft_destroy_mutex(t_data *data, int nb_philo);
t_data			*data_init(char **argv, t_data *data);
int				ft_atoi(const char *str);
long long int	get_time(void);
pthread_mutex_t	*init_forks(t_data *data);
t_philo			**philo_init(t_data *data);
void			philo_start(t_philo **phi);
void			routine(t_philo *philo);
void			philo_think(t_philo *philo);
void			philo_eat(t_philo *philo, int pair_or_imp);
void			philo_eat_02(t_philo *philo, int pair_or_imp);
void			philo_sleep(t_philo *philo);
void			print_instr(t_philo *p, int status);
void			print_fork(t_philo *p);
int				philo_dead(t_philo *philo);
int				verif_arg(int argc, char **argv);

#endif
