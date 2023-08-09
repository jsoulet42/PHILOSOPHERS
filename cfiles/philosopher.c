/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:46:05 by jsoulet           #+#    #+#             */
/*   Updated: 2023/08/09 10:25:37 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hfiles/philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philo;
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	else if (argv[1][0] == '1' && !argv[1][1])
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		printf("0 1 died\n");
		return (0);
	}
	data = data_init(argv, data);
	philo = philo_init(data);
	philo_start(philo);
	free_all(philo, data);
	return (0);
}

/*tout les thread commence ici on les crées et une foit qu'ils ont terminé
	on les join au main_prog afin d'en recuperer le resultat */
void	philo_start(t_philo **phi)
{
	int	i;

	i = 0;
	while (i < phi[0]->data->nb_philo)
	{
		if (pthread_create(phi[i]->thread, NULL, (void *)&routine, phi[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < phi[0]->data->nb_philo)
	{
		if (pthread_join(*phi[i]->thread, NULL) != 0)
			return ;
		i++;
	}
}

void	routine(t_philo *philo)
{
	while (philo->data->nb_meals_max >= philo->nb_meals
		|| philo->data->nb_meals_max < 0)
	{
		pthread_mutex_lock(&philo->data->mdead);
		if (!philo_dead(philo))
		{
			pthread_mutex_unlock(&philo->data->mdead);
			return ;
		}
		if (philo->status != DEAD)
		{
			pthread_mutex_unlock(&philo->data->mdead);
			if (philo->status == THINK)
				philo_think(philo);
			else if (philo->status == EAT && philo->data->nb_philo % 2 == 0)
				philo_eat(philo, 0);
			else if (philo->status == EAT && philo->data->nb_philo % 2 != 0)
				philo_eat(philo, 1);
			else if (philo->status == SLEEP)
				philo_sleep(philo);
		}
		else
			return ;
	}
}
