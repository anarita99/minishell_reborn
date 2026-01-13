/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores & miduarte <adores & miduarte@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:40:50 by adores & mi       #+#    #+#             */
/*   Updated: 2025/11/27 16:44:26 by adores & mi      ###   ########.fr       */
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