/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadigh <kadigh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:17:35 by kadigh            #+#    #+#             */
/*   Updated: 2023/05/11 00:03:16 by kadigh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

u_int64_t   ft_gettime_inms()
{
    struct timeval tv;
    
    if (gettimeofday(&tv, NULL) == -1)
        exit(1);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
#include "time.h"

void    ft_usleep(time_t time)
{
	u_int64_t	start;

	start = ft_gettime_inms();
	while (ft_gettime_inms() - start < time )
		usleep(time);
}

int main(){
	printf("befer\n");
	ft_usleep(10000);
	printf("tozomt\n");
	usleep(10000);
	printf("yazn\n");
}