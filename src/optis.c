/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:52:54 by arocca            #+#    #+#             */
/*   Updated: 2025/03/30 18:32:57 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "printers.h"

bool	running_under_valgrind(void)
{
	int		fd;
	char	buffer[4096];
	ssize_t	bytes_read;

	fd = open("/proc/self/maps", O_RDONLY);
	if (fd < 0)
		return (false);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (ft_strstr(buffer, "valgrind"))
		{
			print_info_str("Program launched under valgrind", NULL);
			return (true);
		}
	}
	return (false);
}

static void	newline(t_maptmp **head, char *line)
{
	t_maptmp	*current;
	t_maptmp	*new_node;

	new_node = malloc(sizeof(t_maptmp));
	if (!new_node)
		return ;
	new_node->line = line;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

bool	free_list(t_maptmp *head, int fd)
{
	char		*line;
	t_maptmp	*tmp;

	if (fd)
	{
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			free(line);
		}
		close(fd);
	}
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
	return (true);
}

static bool	handle_endline(char **line, t_maptmp **head, bool *verif, int fd)
{
	if ((*line)[0] == '\n')
	{
		free((*line));
		if (*head)
			(*verif) = true;
		return (false);
	}
	else
	{
		if ((*verif))
		{
			free((*line));
			free_list(*head, fd);
			return (err("📛 Error : Empty line in map"));
		}
	}
	return (false);
}

bool	read_err(const char *file, t_maptmp **head, int *height)
{
	int			fd;
	bool		map_ended;
	char		*line;

	(*height) = 0;
	*head = NULL;
	map_ended = false;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err_errno(errno));
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
			handle_endline(&line, head, &map_ended, fd);
		else
		{
			if (handle_endline(&line, head, &map_ended, fd))
				break ;
			newline(head, line);
			(*height)++;
		}
		line = get_next_line(fd);
	}
	return (close(fd));
}
