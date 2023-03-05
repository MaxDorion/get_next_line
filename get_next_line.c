/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:24:28 by mdorion           #+#    #+#             */
/*   Updated: 2023/03/05 09:54:04 by mdorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	 if(fd < 0 || BUFFER_SIZE <= 0)
	 	return (NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	return (line);
}

void	read_and_stash(int fd, t_list **ntl)
{
	char	*buff_str;
	int		nbytes;

	nbytes = 1;
	while(!found_new_line(*ntl) && nbytes != 0)
	{ 
		buff_str = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if(!buff_str)
			return;
		nbytes = (int)read(fd, buff_str, BUFFER_SIZE);
		if (*ntl == NULL && nbytes == 0 || nbytes == -1)
		{
			free(buff_str);
			return ;
		}
		buff_str[nbytes] = '\0';
		add_to_stash(ntl, buff_str, nbytes);
		free(buff_str);
	}
}

void	add_to_stash(t_list **stash, char *buff_str, int nbytes)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	i  = 0;
	new_node = malloc(sizeof(t_list));
	if(!new_node)
		return;
	new_node->chain = NULL;
	new_node->line = malloc(sizeof(char) * (nbytes + 1));
	if(!new_node->line)
		return;
	while(buff_str[i] && i < nbytes)
	{
		new_node->line[i] = buff_str[i];
	}
	new_node->line[i] = '\0';
	if (!*stash)
	{
		*stash = new_node;
		return;
	}
	last = go_last(stash);
	last->chain = new_node;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return;
	generate_line(line);
	if (*line == NULL)
		return;
	while (stash)
	{
		i = 0;
		while (stash->line[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->line[i];
				break;
			}
			(*line)[j++] = stash->line[i++];
		}
		stash = stash->chain;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->chain = NULL;
	last = go_last(*stash);
	i = 0;
	while(last->line[i] && last->line[i] != '\n')
		i++;
	if(last->line && last->line[i] == '\n')
		i++;
	clean_node->line = malloc(sizeof(char) * ft_strlen(last->line - i) + 1);
	if(!clean_node)
		return;
	j = 0;
	while(last->line[i])
		clean_node->line[j++] = last->line[i++];
	clean_node->line[j] = '0';
	free_stash(*stash);
	*stash = clean_node;
}