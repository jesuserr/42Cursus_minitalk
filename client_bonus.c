/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:12 by jesuserr          #+#    #+#             */
/*   Updated: 2023/04/11 12:50:02 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	timer(int action)
{
	static struct timeval	start;
	static struct timeval	end;
	long					secs_used;
	long					micros_used;

	if (action == 0)
		gettimeofday(&start, NULL);
	else if (action == 1)
	{
		gettimeofday(&end, NULL);
		secs_used = (end.tv_sec - start.tv_sec);
		micros_used = ((secs_used * 1000000) + end.tv_usec) - (start.tv_usec);
		write (1, "Time: ", 6);
		ft_putnbr_fd((int)micros_used / 1000, 0);
		write (1, " ms\n", 4);
	}
}

int	ft_atoi_mt(char *s)
{
	int	nbr;

	nbr = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		ft_error_handler(ERROR_PID);
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + (*s - 48);
		s++;
	}
	if (nbr == 0 || nbr > PID_MAX)
		ft_error_handler(ERROR_PID);
	return (nbr);
}

void	ft_asc_to_bin(int pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i <= 7)
	{
		bit = (c & 0x80) >> 7;
		usleep(50);
		if (bit == 0)
		{
			if (kill (pid, SIGUSR1) == -1)
				ft_error_handler(ERROR_SIGUSR1);
		}
		else
			if (kill (pid, SIGUSR2) == -1)
				ft_error_handler(ERROR_SIGUSR2);
		c = c << 1;
		i++;
		pause();
	}
}

void	ft_signal_handler(int sig)
{
	static int	i = 1;

	(void)sig;
	write (1, BLUE"\rAcknowledged signals from server: ", 42);
	ft_putnbr_fd (i, 0);
	if (i % 8 == 0)
	{
		write (1, "   Printed bytes on server: ", 28);
		ft_putnbr_fd ((i / 8) - 1, 0);
	}
	i++;
}

int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	struct sigaction	action;	

	if (argc == 3)
	{
		action.sa_handler = ft_signal_handler;
		sigemptyset(&action.sa_mask);
		action.sa_flags = SA_RESTART;
		if (sigaction(SIGUSR1, &action, NULL) == -1)
			ft_error_handler(ERROR_SIG_HANDLER);
		i = 0;
		pid = ft_atoi_mt(argv[1]);
		timer(0);
		while (argv[2][i] != '\0')
			ft_asc_to_bin(pid, argv[2][i++]);
		ft_asc_to_bin(pid, '\0');
		write (1, "\n** End of transmission **\n", 27);
		timer(1);
	}
	else
		write (1, RED"Invalid arguments\n", 25);
	return (0);
}
