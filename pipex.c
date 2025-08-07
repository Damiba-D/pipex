/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:53:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/07 16:25:06 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
After fork:
Parent id = (random)
Child id = 0 

*/

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char *command[] = {"grep", "-E", "c$", "-", 0};
    char *bin_file = command[0];
    if (fork() == 0)
    {
        int redirect_fd = open("red_fd.txt", O_CREAT | O_TRUNC | O_WRONLY);
        dup2(redirect_fd, STDOUT_FILENO);
        close(redirect_fd);
        if(execvp(bin_file, command))
        {
            ft_printf("Error executing %s\n", bin_file);
            exit(EXIT_FAILURE);
        }
    }
    else 
    {
        wait(NULL);
        ft_printf("Done");
    }
    return 0;
}