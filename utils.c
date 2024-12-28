/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:21:33 by abhimi            #+#    #+#             */
/*   Updated: 2024/12/27 18:42:40 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fterror(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free (paths);
	return (NULL);
}

void	ft_exec(char *cmd, char **envp)
{
	char	**cmds;
	char	*path;
	int		i;

	i = 0;
	cmds = ft_split(cmd, ' ');
	if (access(cmds[0], X_OK) == 0)
		path = cmds[0];
	else
		path = find_path(cmds[0], envp);
	if (!path)
	{
		while (cmds[i])
		{
			free(cmds[i]);
			i++;
		}
		free(cmds);
		return ;
	}
	if (execve(path, cmds, envp) == -1)
		perror("execve faild");
}
