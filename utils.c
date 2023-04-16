/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:26:27 by codespace         #+#    #+#             */
/*   Updated: 2023/04/10 07:04:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error_handler(int error)
{
	if (error == ERROR_PID)
		write (1, RED"Invalid Process ID\n", 26);
	else if (error == ERROR_SIGUSR1)
		write (1, RED"Error sending signal SIGUSR1 - Wrong PID ?\n", 50);
	else if (error == ERROR_SIGUSR2)
		write (1, RED"Error sending signal SIGUSR2 - Wrong PID ?\n", 50);
	else if (error == ERROR_SIG_HANDLER)
		write (1, RED"Error installing signal handler\n", 39);
	exit(EXIT_FAILURE);
}
