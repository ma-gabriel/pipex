/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:08:43 by geymat            #+#    #+#             */
/*   Updated: 2024/02/22 17:44:16 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_getenv(char **envp, char *key)
{
	size_t	i;
	int		accurate;

	i = 0;
	accurate = 1;
	while (*envp)
	{
		i = 0;
		accurate = 1;
		while ((*envp)[i] && (*envp)[i] != '=' && accurate && key[i])
		{
			if (key[i] != (*envp)[i])
				accurate = 0;
			i++;
		}
		if (key[i] || (*envp)[i] != '=')
			accurate = 0;
		if (accurate)
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	*ft_strerror(void)
{
	if (errno == 2)
		return ("no such file or directory");
	if (errno == 13)
		return ("permission denied");
	return (strerror(errno));
}

void	print_error(char *name, char *error, char *file)
{
	char	*temp;
	int		i;

	temp = malloc(1);
	if (!temp)
		return ;
	temp[0] = 0;
	temp = ft_strjoin_free_first(temp, name);
	temp = ft_strjoin_free_first(temp, ": ");
	temp = ft_strjoin_free_first(temp, error);
	temp = ft_strjoin_free_first(temp, ": ");
	temp = ft_strjoin_free_first(temp, file);
	temp = ft_strjoin_free_first(temp, "\n");
	if (!temp)
		return ;
	i = 0;
	while (temp[i])
		i++;
	write(2, temp, i);
	free(temp);
}

void	merge_fd(int fd1, int fd2, int fd_res[2])
{
	fd_res[0] = fd1;
	fd_res[1] = fd2;
}

int	main(int argc, char **argv, char *envp[])
{
	int	here_doc;

	if ((argc != 5 && !BONUS) || argc < 5)
	{
		write(2, "Error\nwrong number of arguments\n", 33);
		return (1);
	}
	here_doc = 0;
	if (!ft_strcmp_nl(argv[1], "here_doc"))
	{
		here_doc = 2;
		argv[1] = argv[0];
		argv++;
		if (argc < 6)
			return (1);
	}
	loops_executions(argv, envp, here_doc);
	while (wait(NULL) != -1)
		(void) "we wait LOL";
	return (0);
}
