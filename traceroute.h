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
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <errno.h>

# define FT_SUCCESS	0
# define FT_FAIL	1
# define FT_ERROR	64

# define FT_TRUE	1
# define FT_FALSE	0

# define DOMAIN_LEN	255
# define IPV4_LEN	16

# define MAX_TTL	64
# define PORT_NUM	33434

typedef struct s_info {
	int		udp_sock;
	int		raw_sock;
	char	target_dns[DOMAIN_LEN];
	char	target_ip[IPV4_LEN];
	int		max_ttl;
	int		port_num;
	int		isend;
	int		pid;
}	t_info;

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

void	parse_args(int argc, char **args, t_info *info);

void	error_handling(char *str);
void	invalid_option(char c);
void	unrecognize_error(char *str);
void	help_message(void);

double	diff_timeval(struct timeval time);
int		domain_to_fqdn(char *domain, char *fqdn);
int		domain_to_ip(char *domain, char *ip);
char	*ip_to_domain(struct in_addr addr);

void	process(t_info *info);

#endif