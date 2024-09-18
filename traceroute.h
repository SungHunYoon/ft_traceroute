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
# include <signal.h>
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
# define FT_ERROR	2

# define FT_TRUE	1
# define FT_FALSE	0

# define DOMAIN_LEN 255
# define IPV4_LEN	16

typedef enum e_info {
	PARSE_SUCCESS,
	PARSE_HELP,
	PARSE_INVALID,
	PARSE_HOST,
	PARSE_PKTLEN,
	PARSE_EXTRA,
}	t_parse;

typedef struct s_info {
	int		udp_sock;
	int		raw_sock;
	int		pid;
	char	target_dns[DOMAIN_LEN];
	char	target_ip[IPV4_LEN];
}	t_info;

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

void	parse_args(int argc, char **args, t_info *info);

void	invalid_option(char *str, int idx, int flag);
void	usage_error(char *str, int idx, t_parse type);
void	help_message(void);
void	error_handling(char *str);

double	diff_timeval(struct timeval time);
int		domain_to_fqdn(char *domain, char *fqdn);
int		domain_to_ip(char *domain, char *ip);
char	*ip_to_domain(struct in_addr addr);

void	process(t_info *info);

#endif