/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:18:59 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/09 10:21:25 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

void	free_all(t_philo **philo, t_data *data)
{
	int	i;

	ft_destroy_mutex(data, data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		free(philo[i]->thread);
		free(philo[i]);
		i++;
	}
	free(philo);
	free (data->forks);
	free(data);
}

void	ft_destroy_mutex(t_data *data, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mdead);
	pthread_mutex_destroy(&data->print);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	isneg;

	res = 0;
	isneg = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			isneg = -isneg;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str -48;
		str++;
	}
	return (res * isneg);
}

long long int	get_time(void)
{
	struct timeval	tv;
	long long int	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	print_fork(t_philo *p)
{
	pthread_mutex_lock(&p->data->print);
	printf("%lld %d take a fork\n", get_time() - p->data->st_time, p->id);
	pthread_mutex_unlock(&p->data->print);
}
