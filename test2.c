/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:15:18 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/05/14 22:55:31 by kadigh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:50:25 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/05/14 22:52:29 by kadigh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <sys/time.h>

# define DEAD 0
# define EAT 1
# define SLEEP 2
# define THINK 3

// struct s_philo ;

// typedef	struct s_philo t_philo;

// typedef struct s_forks
// {
// 	int				id;
// 	pthread_mutex_t	*forks;
// }	t_forks;


typedef struct s_vars
{

	int			nbr_of_philos;
	u_int64_t	start_time;
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;
	int			nbrof_meals;
} t_vars;

typedef	struct s_philo
{
	int				id;
	int				state;
	int				*dead;
	pthread_mutex_t	*death_mutex;
	int				meals_count;
	// u_int64_t		start_time;
	u_int64_t		last_meal_time;
	t_vars			*vars;
	pthread_t		*thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef	 struct data
{
	t_vars			vars;
	int				dead;
	pthread_mutex_t	*death_mutex;
	t_philo			*philos;
	pthread_t		*philos_thread;
	pthread_mutex_t	*forks;
	u_int64_t		start_time;
}	t_data;

size_t	ft_strlen(char *s);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(char *str);

void	init_args(int ac, char **av, t_data **data);
u_int64_t   ft_mstime(void);
int		error(char *str);
void	init_vars_struct(t_data **data,int ac, char ** av)
{
	(*data)->vars.nbr_of_philos= ft_atoi(av[1]);
	(*data)->vars.time_to_die= ft_atoi(av[2]);
	(*data)->vars.time_to_eat= ft_atoi(av[3]);
	(*data)->vars.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*data)->vars.nbrof_meals = ft_atoi(av[5]);
	else
		(*data)->vars.nbrof_meals = -1;
	// i = -1;
	// while (++i < (*data)->vars.nbr_of_philos)
	// {
	// 	(*data)->philos[i].vars.nbr_of_philos = ft_atoi(av[1]);
	// 	(*data)->philos[i].vars.time_to_die = ft_atoi(av[2]);	
	// 	(*data)->philos[i].vars.time_to_eat = ft_atoi(av[3]);
	// 	(*data)->philos[i].vars.time_to_sleep = ft_atoi(av[4]);
	// 	if (ac == 6)
	// 		(*data)->philos[i].vars.nbrof_meals = ft_atoi(av[5]);
	// 	else
	// 		(*data)->philos[i].vars.nbrof_meals = -1;
		// i++;
	// }
}

void	init_args(int ac, char **av, t_data	**data)
{
	// (*data)->nbr_of_philos = ft_atoi(av[1]);
	// (*data)->time_to_die = ft_atoi(av[2]);
	// (*data)->time_to_eat = ft_atoi(av[3]);
	// (*data)->time_to_sleep = ft_atoi(av[4]);
	// if (ac == 6)
	// 	(*data)->nbr_of_times_each_philo_must_eat = ft_atoi(av[5]);
	// else
	// 	(*data)->nbr_of_times_each_philo_must_eat = -1;
	(*data)->philos = (t_philo *)ft_calloc((*data)->vars.nbr_of_philos, sizeof(t_philo) );
	(*data)->philos_thread = (pthread_t *)ft_calloc((*data)->vars.nbr_of_philos, sizeof(pthread_t));
	(*data)->forks = (pthread_mutex_t *)ft_calloc((*data)->vars.nbr_of_philos, sizeof(pthread_mutex_t));
	init_vars_struct(data, ac, av);
}

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
		pthread_mutex_init((*data)->forks + i, NULL);
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

	data = ft_calloc(1, sizeof(t_data));
	data->death_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *));
	data->start_time = ft_mstime();
	data->dead = 0;
	if (ac > 6 || ac < 5)
		error("invalid nbr of args\n");
	init_args(ac, av, &data);
	create_philos(&data);
}
