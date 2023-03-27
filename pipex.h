/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tudor <tudor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:11:53 by tudor             #+#    #+#             */
/*   Updated: 2023/03/26 22:42:46 by tudor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "pipex.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	child(char **av, int *pipe_fd, char **envp, int fd);
void	parent(char **av, int *pipe_fd, char **envp, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_error(char *str);
char	*path_finder(char **cmds, char **envp);
char	*search_executable(char *cmd, char *path);
char	*find_path(char **envp);
int		ft_strlen(const char *str);
int		str_ichr(const char *s, int c);

#endif