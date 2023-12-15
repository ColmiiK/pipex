/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:57:17 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/15 11:24:53 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*

	$> <infile ls -l | wc -l >outfile
	./pipex infile "ls -l" "wc -l" outfile
	av[2] -> av[ac - 2] (n pipes)


	data->args[i][0] <- args to check (ls, wc, ...)
	
	if (data->path[i] + data->args[i][0] is accesible)
		all okay, store in data->command
	else
		check next data->path
		

	data->args[i][j][k]:
	
		i ->	{"ls -l"} 
				{"wc -l"}
			
		j ->->		{"ls"}
					{"-l"}
		
		k ->->->		{"l"}
						{"s"}

*/

void ft_access_cmds(t_data *data)
{
	int i;
	int j;
	int k;
	char *temp;

	i = -1;
	j = -1;
	while (data->path[++i])
	{
		k = -1;
		while(data->args[++k][0])
		{
			temp = ft_strjoin(data->path[i], data->args[k][0]); // <- FREE THIS
			if (access(temp, X_OK) != -1)
				data->command[++j] = ft_strdup(temp);
		}
	}
	data->command[++j] = NULL;
}

void ft_parse_cmds(t_data *data, int ac, char **av)
{
	int i;
	int j;

	i = -1;
	j = 1;
	data->args = (char ***)malloc(sizeof(char **) * (ac - 3));
	if (!data->args)
	{
		ft_printf("Error: unable to malloc.\n");
		exit(EXIT_FAILURE);
	}
	while (++j < (ac - 1))
		data->args[++i] = ft_split(av[j], ' ');
	data->args[++i] = ft_calloc(1, 1);
	data->command = (char **)malloc(sizeof(char *) * (ac - 3));
	if (!data->command)
	{
		ft_printf("Error: unable to malloc.\n");
		exit(EXIT_FAILURE);
	}
	ft_access_cmds(data);
}

void ft_find_path(t_data *data, char **envp)
{
	int i;
	int j;
	
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i], ':');
			data->path[0] += 5;
			i = -1;
			while (data->path[++i])
			{
				j = ft_strlen(data->path[i]);
				data->path[i][j] = '/';
			}
			return ;
		}
	}
}

void debug_print(t_data *data, int ac)
{
	ft_printf("Paths:\n");
	for (int i = 0; data->path[i]; i++)
		ft_printf("%s\n", data->path[i]);
	ft_printf("\nArguments:\n");
	for (int i = 0; i < (ac - 3); i++)
	{
		for (int j = 0; data->args[i][j]; j++)
			ft_printf("%s\n", data->args[i][j]);
		ft_printf("\n");
	}
	ft_printf("\nCommands:\n");
	for (int i = 0; data->command[i]; i++)
		ft_printf("%s\n", data->command[i]);
}


int main(int ac, char **av, char **envp)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data *));
	ft_find_path(data, envp);
	ft_parse_cmds(data, ac, av);

	debug_print(data, ac);
	exit(EXIT_SUCCESS);
}
