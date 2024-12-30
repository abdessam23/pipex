/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:33 by abhimi            #+#    #+#             */
/*   Updated: 2024/12/30 12:04:36 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pr_error(char *msg, char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*ppath;
	char	*path;

	i = 0;
	while (!(ft_strncmp(envp[i], "PATH=", 5) == 0))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		ppath = ft_strjoin(paths[i], "/");
		path = ft_strjoin(ppath, cmd);
		free(ppath);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

void	ft_exec(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (access(cmds[0], X_OK) == 0)
		path = cmds[0];
	else
		path = find_path(cmds[0], envp);
	if (!path)
	{
		pr_error("command not found", cmds[0]);
		ft_free(cmds);
		exit (127);
	}
	execve(path, cmds, envp);
	ft_free(cmds);
}
