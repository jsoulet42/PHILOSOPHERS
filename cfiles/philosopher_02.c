/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:18:25 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/09 10:27:03 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

t_data	*data_init(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->st_time = get_time();
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argv[5])
		data->nb_meals_max = ft_atoi(argv[5]);
	else
		data->nb_meals_max = -1;
	data->forks = init_forks(data);
	if (!data->forks)
		return (NULL);
	return (data);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!forks)
		return (NULL);
	pthread_mutex_init(&data->mdead, NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	**philo_init(t_data *data)
{
	int			i;
	t_philo		**philo;

	philo = (t_philo **)malloc(sizeof(t_philo *) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->id = i + 1;
		philo[i]->status = THINK;
		philo[i]->nb_meals = 0;
		philo[i]->last_meal = 0;
		philo[i]->data = data;
		philo[i]->thread = malloc(sizeof(pthread_t));
		i++;
	}
	return (philo);
}

void	print_instr(t_philo *p, int status)
{
	pthread_mutex_lock(&p->data->print);
	if (status == THINK)
		printf("%lld %d is thinking\n", get_time() - p->data->st_time, p->id);
	else if (status == EAT)
		printf("%lld %d is eating\n", get_time() - p->data->st_time, p->id);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n", get_time() - p->data->st_time, p->id);
	else if (status == DEAD)
		printf("%lld %d died\n", get_time() - p->data->st_time, p->id);
	pthread_mutex_unlock(&p->data->print);
}
