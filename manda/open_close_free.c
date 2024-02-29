/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:10:42 by geymat            #+#    #+#             */
/*   Updated: 2024/02/22 17:45:28 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	failed_malloc(int fd[2])
{
	close_3_free(fd[0], fd[1], -1, NULL);
	write(2, "a malloc failed\n", 17);
	exit(1);
}

static int	open_heredocs(char *limiter, int fd[2])
{
	char	*line;
	size_t	len;

	write(2, "pipe heredoc>", 13);
	line = get_next_line(0);
	line || failed_malloc(fd);
	len = ft_strlen(line);
	while (line && ft_strcmp_nl(line, limiter))
	{
		write(fd[1], line, len);
		free(line);
		write(2, "pipe heredoc>", 13);
		line = get_next_line(0);
		line || failed_malloc(fd);
		len = ft_strlen(line);
	}
	if (line)
		free(line);
	close(fd[1]);
	return (fd[0]);
}

int	open_file(char *file, char *name, int flags)
{
	int	fd;
	int	fd_pipe[2];

	if (!flags)
		fd = open(file, O_RDONLY);
	if (flags == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (flags == 2)
	{
		if (pipe(fd_pipe))
		{
			print_error(name, ft_strerror(), "");
			return (-1);
		}
		return (open_heredocs(file, fd_pipe));
	}
	if (flags == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		print_error(name, ft_strerror(), file);
	return (fd);
}

int	close_3_free(int fd1, int fd2, int fd3, void *allocation)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (allocation)
	{
		free(allocation);
		return (-1);
	}
	return (-2);
}

void	free_the_split(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
