/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/04/10 07:07:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_print_info(int *count)
{
	write (1, BLUE"\n** End of transmission **", 33);
	write (1, "\nPrinted bytes: ", 16);
	ft_putnbr_fd(*count - 1, 0);
	write (1, "\n\nServer Up - Process ID: ", 26);
	ft_putnbr_fd(getpid(), 0);
	write (1, "\nWaiting for new transmission: "WHITE, 38);
	*count = 0;
}		

void	ft_signal_handler(int sig)
{
	static int	i = 0;
	static char	c = 0;
	static int	count = 0;

	c = c << 1;
	i++;
	if (sig == SIGUSR2)
		c = c | 0x01;
	if (i == 8)
	{
		write (1, &c, 1);
		count++;
		if (c == '\0')
			ft_print_info(&count);
		c = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		if ((signal(SIGUSR1, ft_signal_handler)) == SIG_ERR
			|| (signal(SIGUSR2, ft_signal_handler) == SIG_ERR))
			ft_error_handler(ERROR_SIG_HANDLER);
		write (1, BLUE"Server Up - Process ID: ", 31);
		ft_putnbr_fd(getpid(), 0);
		write (1, "\nWaiting for transmission: "WHITE, 34);
		while (1)
			pause();
	}
	write (1, RED"Invalid arguments\n", 25);
	return (0);
}
