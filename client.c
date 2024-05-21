/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:09:29 by med-dahr          #+#    #+#             */
/*   Updated: 2024/05/20 14:26:16 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	extract_pid(char k, int num)
{
	num *= 10;
	num += k - '0';
	return (num);
}

void	send_sig(char k, int pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (k >> bit & 1)
			kill(pid, SIGUSR2);
		else
		{
			kill(pid, SIGUSR1); 
		}
		bit--;
		usleep(300);
	}
}

void	send_bits(int pid, char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		send_sig(msg[len++], pid);
	send_sig('\0', pid);
}

int	main(int ac, char **av)
{
	t_tls	tol;

	tol.id = 0;
	tol.len = 0;
	if (ac != 3)
		exit(write(2, "ERROR ARGUMENT\n", 15 - 1));
	while (av[1][tol.len])
	{
		if (av[1][tol.len] >= '0' && av[1][tol.len] <= '9')
			tol.id = extract_pid(av[1][tol.len++], tol.id);
		else
			exit(write(2, "ERROR PID FORMAT\n", 17));
	}
	if (tol.id <= 0)
		exit(write(2, "PID NOT EXIST\n", 14 - 1));
	send_bits(tol.id, av[2]);
	return (0);
}
