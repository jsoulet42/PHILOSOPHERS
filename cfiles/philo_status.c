/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:24:08 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/09 10:27:25 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	philo_think(t_philo *philo)
{
	print_instr(philo, THINK);
	philo->status = EAT;
}

void	philo_eat(t_philo *philo, int pair_or_imp)
{
	if (philo->id % 2 != 0)
	{
		if (philo->id == philo->data->nb_philo && pair_or_imp == 1)
		{
			pthread_mutex_lock(&philo->data->forks[philo->id - 2]);
			pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
			print_fork(philo);
			print_fork(philo);
		}
		else
		{
			pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
			pthread_mutex_lock(&philo->data->forks[philo->id]);
			print_fork(philo);
			print_fork(philo);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->id - 2]);
		pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
		print_fork(philo);
		print_fork(philo);
	}
	philo_eat_02(philo, pair_or_imp);
}

void	philo_eat_02(t_philo *philo, int pair_or_imp)
{
	print_instr(philo, EAT);
	philo->nb_meals++;
	philo->last_meal = get_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->status = SLEEP;
	if (philo->id % 2 != 0)
	{
		if (philo->id == philo->data->nb_philo && pair_or_imp == 1)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->id - 2]);
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->forks[philo->id]);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id - 2]);
		pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	}
}

void	philo_sleep(t_philo *philo)
{
	print_instr(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	philo->status = THINK;
}

int	philo_dead(t_philo *philo)
{
	int	get_return;

	if (philo->data->dead == 1)
		return (0);
	get_return = get_time() - philo->last_meal;
	if (get_return > philo->data->time_to_die)
	{
		print_instr(philo, DEAD);
		philo->status = DEAD;
		philo->data->dead = 1;
		return (0);
	}
	else if (philo->data->dead == 1)
		return (0);
	return (1);
}
