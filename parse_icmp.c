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

int	set_router_info(t_info *info, struct ip *ip_hdr, \
	struct icmp *icmp_hdr, struct upd_hdr *udp_hdr)
{
	char	*ip_src;

	ip_src = inet_ntoa(ip_hdr->ip_src);
	if (icmp_hdr->icmp_type == ICMP_UNREACH && \
		icmp_hdr->icmp_code == ICMP_UNREACH_PORT)
	{
		info->isend = FT_TRUE;
		ft_strncmp(info->router_ip, ip_src, ft_strlen(ip_src));
	}
	else if (icmp_hdr->icmp_type == ICMP_TIMXCEED)
		ft_strncmp(info->router_ip, ip_src, ft_strlen(ip_src));
	else if (icmp_hdr->icmp_type == ICMP_UNREACH && \
			icmp_hdr->icmp_code == ICMP_UNREACH_HOST)
		info->error = 'H';
	else
		return (FT_FAIL);
	return (FT_SUCCESS);
}

int	parse_icmp_packet(t_info *info, char *buf)
{
	struct ip		ip_hdr;
	struct icmp		icmp_hdr;
	struct udphdr	udp_hdr;

	ft_memcpy(&ip_hdr, buf, IP_SIZE);
	ft_memcpy(&icmp_hdr, &buf[IP_SIZE], ICMP_SIZE);
	ft_memcpy(&udp_hdr, &buf[IP_SIZE + ICMP_SIZE], UDP_SIZE);
	if (info->dst_addr.sin_addr.s_addr != ntohl(icmp_hdr.icmp_ip.ip_src.s_addr))
		return (FT_FAIL);
	if (info->dst_addr.sin_port != ntohs(udp_hdr.uh_dport))
		return (FT_FAIL);
	return (set_router_info(info, &ip_hdr, &icmp_hdr, &udp_hdr));
}

int	recv_icmp_packet(t_info *info)
{
	char	buf[1024];
	size_t	socksize;

	if (recvfrom(info->raw_sock, buf, sizeof(buf), 0, \
		(struct sockaddr *)&info->src_addr, &socksize) < 0)
		error_handling("recvfrom error");
	return (parse_icmp_packet(info, buf));
}
