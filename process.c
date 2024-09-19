/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:50:06 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/19 12:50:19 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

volatile sig_atomic_t	g_stop;

static void	sigint_handler(int signo)
{
	(void)signo;
	g_stop = 1;
}

static void	initialize(t_info *info)
{
	socklen_t	optlen;
	uint8_t		ttl;

	printf("traceroute to %s (%s), ", info->target_dns, info->target_ip);
	printf("30 hops max, 60 byte packets\n");
	signal(SIGINT, sigint_handler);
	info->udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (info->udp_sock < 0)
		error_handling("socket UDP error");
	info->raw_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (info->raw_sock < 0)
		error_handling("socket RAW error");
	ttl = 30;
	optlen = sizeof(ttl);
	if (setsockopt(info->udp_sock, IPPROTO_IP, IP_TTL, &ttl, optlen) < 0)
		error_handling("setsockopt TTL error");
	info->pid = getpid();
}

void	process(t_info *info)
{
	initialize(info);
}
