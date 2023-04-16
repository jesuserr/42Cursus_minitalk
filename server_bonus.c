/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:50 by jesuserr          #+#    #+#             */
/*   Updated: 2023/04/11 11:59:37 by jesuserr         ###   ########.fr       */
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

void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	c = 0;
	static int	count = 0;

	(void)context;
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
	usleep(100);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error_handler(ERROR_SIGUSR1);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	(void)argv;
	if (argc == 1)
	{
		action.sa_sigaction = ft_signal_handler;
		sigemptyset(&action.sa_mask);
		action.sa_flags = SA_RESTART | SA_SIGINFO;
		if ((sigaction(SIGUSR1, &action, NULL) == -1)
			|| (sigaction(SIGUSR2, &action, NULL) == -1))
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
