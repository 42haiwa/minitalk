/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:52:55 by cjouenne          #+#    #+#             */
/*   Updated: 2023/11/02 15:40:27 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>
#include <signal.h>

void	send_char(pid_t	s_pid, char c)
{
	ssize_t	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 0x1)
			kill(s_pid, SIGUSR2);
		else
			kill(s_pid, SIGUSR1);
		usleep(200);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	s_pid;
	ssize_t	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Usage: ./client <pid> \"STR\"\n");
		return (0);
	}
	s_pid = ft_atoi(argv[1]);
	while (argv[2][i])
	{
		send_char(s_pid, argv[2][i]);
		i++;
	}
	send_char(s_pid, '\n');
	send_char(s_pid, '\0');
	return (0);
}
