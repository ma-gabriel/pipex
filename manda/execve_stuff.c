/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:54:44 by geymat            #+#    #+#             */
/*   Updated: 2024/02/22 10:40:59 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char **paths, char *command, char *name)
{
	int		i;
	char	*path;

	if (!paths)
		return (NULL);
	path = ft_strdup_until_space(command);
	i = 0;
	while (!ft_strchr(command, '/') && path && access(path, X_OK) && paths[i])
	{
		free(path);
		path = ft_strjoinwithslash(paths[i++], command);
	}
	if (path && access(path, X_OK))
	{
		if (ft_strchr(command, '/'))
			print_error(name, ft_strerror(), path);
		else
			print_error(name, "command not found", path
				+ ft_strlen(paths[i - 1]) + 1);
		free(path);
		path = NULL;
	}
	free_the_split(paths);
	return (path);
}


int	middle_command(char **argv, char **envp, int fd[3], char *name)
{
	char	*command;

	if (fd[0] == -1 || fd[1] == -1 || dup2(fd[1], 1) == -1
		|| dup2(fd[0], 0) == -1)
		return (close_3_free(fd[0], fd[1], -1, NULL));
	command = find_command(ft_split(ft_getenv(envp, "PATH") + 5, ':'),
			argv[0], name);
	if (!command)
		return (close_3_free(fd[0], fd[1], -1, NULL));
	argv = ft_split(argv[0], ' ');
	if (!argv)
		return (close_3_free(fd[0], fd[1], -1, command));
	close_3_free(fd[0], fd[1], -1, NULL);
	execve(command, argv, envp);
	free_the_split(argv);
	free(command);
	return (0);
}


int	the_execve_stuff(char **argv, char *envp[], int fd[3], size_t index)
{
	int	pid;

	pid = fork();
	if (pid != 0)
		return (pid < 0);
	if (fd[2] != -1)
		close(fd[2]);
	fd[2] = -1;
	middle_command(argv + index, envp, fd, *argv);
	close_3_free(0, 1, -1, NULL);
	exit(1);
}

void	loops_executions(char **argv, char *envp[], int bonus)
{
	size_t	i;
	int		fd_old[2];
	int		fd_new[2];
	int		fd_merged[3];

	i = 1;
	merge_fd(open_file(argv[1], *argv, bonus), -1, fd_old);
	while (argv[++i + 1])
	{
		if (argv[i + 2] && pipe(fd_new))
			exit(close_3_free(fd_old[0], fd_old[1], -1, NULL));
		if (!argv[i + 2])
			merge_fd(-1, open_file(argv[i + 1], *argv, 1 + bonus), fd_new);
		merge_fd(fd_old[0], fd_new[1], fd_merged);
		fd_merged[2] = fd_new[0];
		if (the_execve_stuff(argv, envp, fd_merged, i))
		{
			if (fd_new[0] != -1)
				close(fd_new[0]);
			exit(close_3_free(fd_old[0], fd_old[1], fd_new[1], NULL));
		}
		close_3_free(fd_old[0], fd_old[1], fd_new[1], NULL);
		fd_old[0] = fd_new[0];
	}
	close_3_free(fd_old[0], fd_old[1], -1, NULL);
}
