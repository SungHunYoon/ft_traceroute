/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:50:06 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/19 21:26:51 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	set_next_packet_info(t_info *info, int inc_flag)
{
	socklen_t	optlen;

	if (inc_flag)
	{
		info->ttl++;
		info->port_num++;
	}
	optlen = sizeof(info->ttl);
	if (setsockopt(info->udp_sock, IPPROTO_IP, IP_TTL, &info->ttl, optlen) < 0)
		error_handling("setsockopt error");
	info->dest_addr.sin_port = htons(info->port_num);
	info->prev = 0;
}

static void	initialize(t_info *info)
{
	struct in_addr	ip_addr;

	printf("traceroute to %s (%s), ", info->target_dns, info->target_ip);
	printf("64 hops max\n");
	info->udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (info->udp_sock < 0)
		error_handling("socket UDP error");
	info->raw_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (info->raw_sock < 0)
		error_handling("socket RAW error");
	if (inet_pton(AF_INET, info->target_ip, &ip_addr) < 1)
		error_handling("inet_pton error");
	info->dest_addr.sin_family = AF_INET;
	info->dest_addr.sin_addr = ip_addr;
	info->ttl = 1;
	info->port_num = PORT_NUM;
	set_next_packet_info(info, FT_FALSE);
	info->max_ttl = MAX_TTL;
	info->pid = getpid();
}

static void	send_udp_packet(t_info *info)
{
	const char	msg[] = "SUPERMAN";

	if (sendto(info->udp_sock, msg, sizeof(msg), 0, \
		(struct sockaddr *)&info->dest_addr, sizeof(info->dest_addr)) < 0)
		error_handling("sendto error");
	gettimeofday(&info->time, NULL);
}

static int	recv_process(t_info *info)
{
	fd_set 			reads;
	struct timeval	timeout;
	double			diff_time;
	size_t			tmp;
	int				ret;

	diff_time = diff_timeval(info->time);
	while (diff_time <= TIMEOUT_MS)
	{
		FD_ZERO(&reads);
		FD_SET(info->raw_sock, &reads);
		tmp = ((TIMEOUT_MS * TIME_MS) - (size_t)(diff_time * TIME_MS));
		timeout.tv_sec = tmp / TIME_US;
		timeout.tv_usec = tmp % TIME_US;
		ret = select(info->raw_sock + 1, &reads, NULL, NULL, &timeout);
		if (ret < 0)
			error_handling("select error");
		if (ret > 0 && FD_ISSET(info->raw_sock, &reads) && \
			recv_icmp_packet(info))
			return (FT_SUCCESS);
		diff_time = diff_timeval(info->time);
	}
	return (FT_FAIL);
}

void	process(t_info *info)
{
	int	cnt;

	initialize(info);
	while (info->ttl <= info->max_ttl && !info->isend)
	{
		printf(" %2d ", info->ttl);
		cnt = 0;
		while (cnt < ROUTE_CNT)
		{
			send_udp_packet(info);
			if (recv_process(info) == FT_SUCCESS)
			{
				if (cnt == 0 || info->prev != info->src_addr.sin_addr.s_addr)
					printf(" %s ", inet_ntoa(info->src_addr.sin_addr));
				printf(" %.3fms ", diff_timeval(info->time));
				info->prev = info->src_addr.sin_addr.s_addr;
			}
			else
				printf(" * ");
			fflush(stdout);
			cnt++;
		}
		printf("\n");
		set_next_packet_info(info, FT_TRUE);
	}
}
