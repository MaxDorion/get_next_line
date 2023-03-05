/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:24:32 by mdorion           #+#    #+#             */
/*   Updated: 2023/03/05 09:51:11 by mdorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int found_newline(t_list *stash)
{
	int	i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = go_last(stash);
	i = 0;
	while (current->line[i])
	{
		if (current->line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*go_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while(current && current->chain)
		current = current->chain;
	return (current);
}

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while(stash)
	{
		i = 0;
		while(stash->line[i])
		{
			if (stash->line[i] == '\n')
			{
				len++;
				break;
			}
			len++;
			i++;
		}
	}
	*line = malloc (sizeof(char) * (len + 1));
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while(str[len])
		len++;
	return(len);
}