/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:13 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:38:13 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <netdb.h>
# include <errno.h>

# define FT_SUCCESS	0
# define FT_FAIL	1
# define FT_ERROR	64

# define FT_TRUE	1
# define FT_FALSE	0

# define DOMAIN_LEN	255
# define IPV4_LEN	16

# define TIME_MS	1000
# define TIME_US	1000000
# define TIMEOUT_MS	3000

# define ROUTE_CNT	3
# define MAX_TTL	64
# define PORT_NUM	33434

# define IP_SIZE	20
# define ICMP_SIZE	28
# define UDP_SIZE	8

typedef struct s_info {
	int					udp_sock;
	int					raw_sock;
	char				target_dns[DOMAIN_LEN];
	char				target_ip[IPV4_LEN];
	struct sockaddr_in	src_addr;
	struct sockaddr_in	dst_addr;
	char				router_ip[IPV4_LEN];
	char				error;
	in_addr_t			prev;
	uint8_t				ttl;
	int					port_num;
	int					max_ttl;
	int					isend;
	struct timeval		time;
	int					pid;
}	t_info;

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void	parse_args(int argc, char **args, t_info *info);

void	error_handling(char *str);
void	invalid_option(char c);
void	unrecognize_error(char *str);
void	missing_host_error(void);
void	help_message(void);

double	diff_timeval(struct timeval time);
int		domain_to_fqdn(char *domain, char *fqdn);
int		domain_to_ip(char *domain, char *ip);
char	*ip_to_domain(struct in_addr addr);

void	process(t_info *info);

int		recv_icmp_packet(t_info *info);

#endif