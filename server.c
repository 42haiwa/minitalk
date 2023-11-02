/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:52:13 by cjouenne          #+#    #+#             */
/*   Updated: 2023/11/02 15:53:20 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>
#include <signal.h>

static void	add_to2(char **s, char **tmp, char c_data)
{
	*s = ft_calloc(ft_strlen(*tmp) + 2, 1);
	if (!(*s))
		return ;
	ft_strlcpy(*s, *tmp, ft_strlen(*tmp) + 1);
	ft_strlcat(*s, &c_data, ft_strlen(*s) + 2);
}

static void	add_to(char **s, int data)
{
	char	*tmp;
	char	c_data;

	if (data == 0)
		return ;
	c_data = (char) data;
	if ((*s)[0] == 0)
	{
		free(*s);
		*s = ft_calloc(2, 1);
		if (!(*s))
			return ;
		(*s)[0] = c_data;
		return ;
	}
	tmp = ft_strdup(*s);
	if (!tmp)
		return ;
	free(*s);
	add_to2(s, &tmp, c_data);
	free(tmp);
}

int	print_str(char **s, int data)
{
	if (ft_strlen(*s) == 0)
	{
		free(*s);
		*s = ft_calloc(2, 1);
		if (!(*s))
			return (1);
	}
	if (data == 0)
	{
		ft_printf("%s\n", *s);
		free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

void	signal_handler(int sig)
{
	static int	data = 0x0;
	static int	n = 0;
	static char	*s = NULL;

	if (s == NULL)
		s = ft_calloc(1, 1);
	if (!s)
		return ;
	if (sig == SIGUSR2)
		data |= (0x1 << n);
	n++;
	if (n == 8)
	{
		n = 0;
		if (print_str(&s, data))
			return ;
		add_to(&s, data);
		data = 0x0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = signal_handler;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
