/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungyoon <sungyoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:38:19 by sungyoon          #+#    #+#             */
/*   Updated: 2024/09/18 19:38:20 by sungyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

void	error_handling(char *str)
{
	dprintf(2, "ft_traceroute: %s\n", str);
	exit(FT_FAIL);
}

void	invalid_option(char c)
{
	dprintf(2, "ft_traceroute: invalid option -- '%c'\n", c);
	dprintf(2, "Try 'ft_traceroute --help' for more information.\n");
	exit(FT_ERROR);
}

void	unrecognize_error(char *str)
{
	dprintf(2, "ft_traceroute: unrecognized option '%s'\n", str);
	dprintf(2, "Try 'ft_traceroute --help' for more information.\n");
	exit(FT_ERROR);
}

void	missing_host_error(void)
{
	dprintf(2, "ft_traceroute: missing host operand\n");
	dprintf(2, "Try 'ft_traceroute --help' for more information.\n");
	exit(FT_ERROR);
}

void	help_message(void)
{
	printf("Usage: ft_traceroute [OPTION...] HOST\n");
	printf("Print the route packets trace to network host.\n\n");
	printf("  -h, --help                 ");
	printf("give this help list\n\n");
	printf("Mandatory or optional arguments to long options are also ");
	printf("mandatory or optional\nfor any corresponding short options.\n\n");
	printf("Report bugs to <sungyoon@student.42seoul.kr>.\n");
	exit(FT_SUCCESS);
}
