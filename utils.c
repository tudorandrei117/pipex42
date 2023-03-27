/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tudor <tudor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:15:14 by tudor             #+#    #+#             */
/*   Updated: 2023/03/26 22:42:33 by tudor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	str_ichr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((str1[i] == str2[i]) && str1[i])
	{
		if (i < (n - 1))
		i++;
		else
		{
			return (0);
		}
	}
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char	*search_executable(char *cmd, char *path)
{
	char	*dir;
	char	*bin;

	while (path && str_ichr(path, ':') > -1)
	{
		dir = ft_substr(path, 0, str_ichr(path, ':'));
		bin = ft_strjoin(ft_strjoin(dir, "/"), cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (NULL);
}

char	*path_finder(char **cmds, char **envp)
{
	char	*cmd;
	char	*path;
	char	*bin;

	cmd = cmds[0];
	path = find_path(envp);
	if (!path)
		return (cmd);
	bin = search_executable(cmd, path);
	if (!bin)
		return (cmd);
	return (bin);
}
