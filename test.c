/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:39:13 by kadigh            #+#    #+#             */
/*   Updated: 2023/05/12 01:02:42 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
struct vars 
{
    int i;
    pthread_mutex_t m;
    
};

void	*test(void *arg)
{
    struct vars v = *(struct vars *)arg;
    pthread_mutex_lock(&v.m);
    // printf("%d\t",v.i);
    if (v.i == 0 )
    {
        printf("%d\t",v.i);
        printf("hello1\n");
    }
    else if (v.i == 1)
    {
        printf("%d\t",v.i);
        printf("hello2\n");
    }
    else if (v.i == 2)
    {
        printf("%d\t",v.i);
        printf("hello3\n");
    }
    pthread_mutex_unlock(&v.m);
    return (NULL);
}
int main()
{
    pthread_t *t;
    
    struct vars v[3];
    int i = 0;
    v[0].i = 0;
    t = (pthread_t *)malloc(sizeof(pthread_t) * 3);
    // v[i].m = (pthread_mutex_t *)malloc(3 * sizeof(pthread_mutex_t));
    // pthread_mutex_init(&v[i].m, NULL);

    while (i < 3)
    {
        pthread_mutex_init(&v[i].m, NULL);
        v[i].i = i;
        i++;
    }
    i = 0;
    while (i < 3)
    {
        printf("op\n");
        pthread_create(t + i, NULL, test, v + i);
        v[i].i = i;
        i++;
    }
    
    i = 0;
    
    while (i < 3)
    {
        pthread_join(t[i], NULL);
        printf("oppp\n");     
        i++;
    }
    i = 0;
    pthread_mutex_destroy(&v[i].m);
}
