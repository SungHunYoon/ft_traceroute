/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_icmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:23:50 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/21 11:23:52 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	set_error_code(t_info *info, struct icmp *icmp_hdr)
{
	if (icmp_hdr->icmp_type != ICMP_UNREACH)
		return ;
	if (icmp_hdr->icmp_code == ICMP_UNREACH_NET)
		info->error = 'N';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_HOST)
		info->error = 'H';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_PROTOCOL)
		info->error = 'P';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_NEEDFRAG)
		info->error = 'F';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_SRCFAIL)
		info->error = 'S';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_FILTER_PROHIB)
		info->error = 'X';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_HOST_PRECEDENCE)
		info->error = 'V';
	else if (icmp_hdr->icmp_code == ICMP_UNREACH_PRECEDENCE_CUTOFF)
		info->error = 'C';
	else
		info->error = icmp_hdr->icmp_code + '0';
}

static int	set_router_info(t_info *info, struct icmp *icmp_hdr)
{
	int	ret;

	ret = FT_FAIL;
	if (icmp_hdr->icmp_type == ICMP_UNREACH)
	{
		info->isend = FT_TRUE;
		ret = FT_SUCCESS;
		if (icmp_hdr->icmp_code != ICMP_UNREACH_PORT)
			set_error_code(info, icmp_hdr);
	}
	else if (icmp_hdr->icmp_type == ICMP_TIMXCEED)
		ret = FT_SUCCESS;
	return (ret);
}

int	parse_icmp_packet(t_info *info, char *buf)
{
	struct ip		ip_hdr;
	struct icmp		icmp_hdr;
	struct udphdr	udp_hdr;

	ft_memcpy(&ip_hdr, buf, IP_SIZE);
	ft_memcpy(&icmp_hdr, &buf[IP_SIZE], ICMP_SIZE);
	ft_memcpy(&udp_hdr, &buf[IP_SIZE + ICMP_SIZE], UDP_SIZE);
	if ((info->bind_addr.sin_port != udp_hdr.uh_sport) || \
		(info->dst_addr.sin_port != udp_hdr.uh_dport))
		return (FT_FAIL);
	return (set_router_info(info, &icmp_hdr));
}

int	recv_icmp_packet(t_info *info)
{
	char		buf[1024];
	socklen_t	socksize;

	socksize = sizeof(info->src_addr);
	if (recvfrom(info->raw_sock, buf, sizeof(buf), 0, \
		(struct sockaddr *)&info->src_addr, &socksize) < 0)
		error_handling("recvfrom error");
	return (parse_icmp_packet(info, buf));
}
