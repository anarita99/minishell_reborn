/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:40 by adores            #+#    #+#             */
/*   Updated: 2026/01/15 15:12:41 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "execution.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int file = open("file.txt", O_WRONLY | O_CREAT , 0777);
	//int dup_stdout = dup(STDOUT_FILENO);
	
	dup2(file, STDOUT_FILENO);
	close(file);
	printf("OLA");
	

	/*dup2(dup_stdout, STDOUT_FILENO);
	close(dup_stdout);
	printf("ola2\n");
	*/
}