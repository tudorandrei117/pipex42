/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tudor <tudor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:50 by tudor             #+#    #+#             */
/*   Updated: 2023/03/27 15:43:04 by tudor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	child(char **argv, int *pipe_fd, char **envp, int fd)
{
	char	**cmds;

	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	cmds = ft_split(argv[2], ' ');
	execve(path_finder(cmds, envp), cmds, NULL);
}

void	parent(char **argv, int *pipe_fd, char **envp, int fd)
{
	char	**cmds;

	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	cmds = ft_split(argv[3], ' ');
	execve(path_finder(cmds, envp), cmds, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int file1;
	int file2;
	int pipe_fd[2];
	pid_t pid;

	if (argc != 5)
		ft_error("Invalid parameters!\n");
	file1 = open(argv[1], O_CREAT | O_RDWR);
	file2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file1 < 0 || file2 < 0)
		ft_error("Error opening infile/outfile\n");
	if (pipe(pipe_fd) == -1)
		ft_error("Error creating the pipe");
	pid = fork();
	if (pid == -1)
		ft_error("Error creating a fork");
	if (pid == 0)
		child(argv, pipe_fd, envp, file1);
	parent(argv, pipe_fd, envp, file2);
	return (0);
}