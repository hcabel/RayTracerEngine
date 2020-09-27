/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 22:46:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/26 16:43:07 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(int argc, char **argv)
{
	t_info	info;
	int		code_error;

	(void)argc;
	if ((code_error = init(&info, argv[1])) != GOOD)
		return (program_exit(&info, code_error));
	if ((code_error = loop(&info)) != GOOD)
		return (program_exit(&info, code_error));
	return (program_exit(&info, GOOD));
}
