/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:58:19 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 16:06:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		all_threads_are_done(t_sampling *sampling)
{
	while (pthread_mutex_trylock(&sampling->mutex))
		;
	if (sampling->threads_status == powf(2, RAYMARCHING_THREAD) - 1)
	{
		pthread_mutex_unlock(&sampling->mutex);
		return (GOOD);
	}
	pthread_mutex_unlock(&sampling->mutex);
	return (FAILED);
}
