/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:08 by alvega-g          #+#    #+#             */
/*   Updated: 2023/12/13 13:53:40 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft/include/libft.h"
#include <sys/wait.h>

typedef struct s_data
{
	char **path;
	char ***command;


}	t_data;

#endif