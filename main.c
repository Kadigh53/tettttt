/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:50:25 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/05/14 23:23:52 by kadigh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	pick_forks(t_philo *philo)
// {
// 	philo->right_fork = philo->id;
// 	pthread_mutex_lock(philo->right_fork);
// 	print_status(philo, "has taken a fork");
// 	pthread_mutex_lock(philo->left_fork);
// 	print_status(philo, "has taken a fork");
// 	print_status(philo, "is eating");
// 	philo->last_meal = get_time();
// }
# define time_x 1
void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%lu\t%d\thas taken a fork\n",ft_mstime() - philo->vars->start_time, philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%lu\t%d\thas taken a fork\n",ft_mstime() - philo->vars->start_time, philo->id);
	printf("%lu\t%d\tis eating\n",ft_mstime() - philo->vars->start_time, philo->id);
	philo->meals_count++;
	philo->last_meal_time = ft_mstime();
	usleep(philo->vars->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	printf("%lu\t%d\tis sleeping\n",ft_mstime() - philo->vars->start_time,philo->id);
	usleep(philo->vars->time_to_sleep * 1000);
}

void	eating(t_philo	*philo)
{
	pick_forks(philo);
	usleep(philo->vars->time_to_eat * 1000);
	drop_forks(philo);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (ft_mstime() - philo->last_meal_time >= philo->vars->time_to_die && *philo->dead != 1)
	{
		*philo->dead = 1;
		printf("%lu\t%d\tdead\n",ft_mstime() - philo->vars->start_time,philo->id);
		exit(0);
	}
	pthread_mutex_unlock(philo->death_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(2000);
	while (1)
	{
		if (philo->meals_count >= philo->vars->nbrof_meals && philo->vars->nbrof_meals != -1)
			break;
		check_death(philo);
		eating(philo);
	}
	return (NULL);
}

void	create_philos(t_data **data)
{
	int i;

	i = -1;
	(*data)->dead = 0;
	pthread_mutex_init((*data)->death_mutex, NULL);
	while (++i < (*data)->vars.nbr_of_philos)
	{
		pthread_mutex_init(&(*data)->forks[i], NULL);
		(*data)->philos[i].thread_id = &(*data)->philos_thread[i];
		if (i  == (*data)->vars.nbr_of_philos - 1)
		{
			(*data)->philos[i].right_fork = &(*data)->forks[i];
			(*data)->philos[i].left_fork = &(*data)->forks[0];
		}
		else
		{
			(*data)->philos[i].right_fork = &(*data)->forks[i];
			(*data)->philos[i].left_fork = &(*data)->forks[i + 1];
		}
		// ((*data)->philos + i)->start_time = ft_mstime();
		((*data)->philos + i)->last_meal_time = ft_mstime();
		((*data)->philos + i)->meals_count = 0;
		((*data)->philos + i)->id = i + 1;
		((*data)->philos + i)->dead = &(*data)->dead;
		((*data)->philos + i)->death_mutex = (*data)->death_mutex;
		((*data)->philos + i)->vars = &(*data)->vars;
	}
	printf("%lu %ld  %d\t\tstarted\n\n",ft_mstime() , (*data)->start_time, 1);
	i = -1;
	while (++i < (*data)->vars.nbr_of_philos)
	{
		pthread_create((*data)->philos_thread + i, NULL, routine, &(*data)->philos[i]);
	}
	i = -1;
	while (++i < (*data)->vars.nbr_of_philos)
		pthread_join((*data)->philos_thread[i], NULL);
	i = -1;
	while (++i < (*data)->vars.nbr_of_philos)
		pthread_mutex_destroy((*data)->forks + i);
	pthread_mutex_destroy((*data)->death_mutex);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	data->death_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *));
	// data->philos = (t_philo *)calloc(data->vars.nbr_of_philos+1, sizeof(t_philo) );
	// data->philos_thread = (pthread_t *)calloc(data->vars.nbr_of_philos+1, sizeof(pthread_t));
	// data->forks = (pthread_mutex_t *)calloc(data->vars.nbr_of_philos + 1, sizeof(pthread_mutex_t));
	data->start_time = ft_mstime();
	data->dead = 0;
	if (ac > 6 || ac < 5)
		error("invalid nbr of args\n");
	init_args(ac, av, &data);
	create_philos(&data);
}

