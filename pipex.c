/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:47:06 by abhimi            #+#    #+#             */
/*   Updated: 2024/12/30 11:49:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(int *fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		pr_error("open","failed");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	ft_exec(argv[2], envp);
}

void	ft_parent_process(int *fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		pr_error("open","failed");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	ft_exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			pr_error("pipe failed","!");
		}
		pid = fork();
		if (pid < 0)
			 pr_error("fork failed","!");
		if (pid == 0)
			ft_child_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		ft_parent_process(fd, argv, envp);
	}
	else
	{
		pr_error("bad argument","\nex: ./pipex infile cmd1 cmd2 outfile\n");
	}
	return (0);
}
