/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:40:12 by geymat            #+#    #+#             */
/*   Updated: 2024/02/22 17:34:55 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# ifndef BONUS
#  define BONUS 0
# endif

char	**ft_split(char const *s, char c);
char	*ft_strjoin_free_first(char *s1, char *s2);
char	*ft_strjoinwithslash(char const *s1, char const *s2);
size_t	ft_strlen(char *s1);
size_t	ft_wordlen(char *s1);
void	merge_fd(int fd1, int fd2, int fd_res[2]);
char	*ft_getenv(char **envp, char *key);
int		close_3_free(int fd1, int fd2, int fd3, void *allocation);
void	free_the_split(char **argv);
void	print_error(char *name, char *error, char *file);
int		open_file(char *file, char *name, int flags);
char	*ft_strerror(void);
int		ft_strcmp_nl(const char *first, const char *second);
char	*get_next_line(int fd);
void	loops_executions(char **argv, char *envp[], int bonus);
char	*ft_strchr(char *str, int c);
char	*ft_strdup_until_space(const char *src);

#endif
