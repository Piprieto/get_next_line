/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piprieto <piprieto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:18:59 by piprieto          #+#    #+#             */
/*   Updated: 2024/12/17 12:24:50 by piprieto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_read(char *buffer, char *res)
{
	char	*temp;

	temp = ft_strjoin(buffer, res);
	free(buffer);
	return (temp);
}

char	*read_file(int fd, char *data_read)
{
	char	*temp;
	int		byte_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (free(data_read), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(temp), free(data_read), NULL);
		temp[byte_read] = '\0';
		data_read = ft_free_read (data_read, temp);
		if (!data_read)
			return (free(temp), NULL);
		if (ft_strchr(data_read, '\n'))
			break ;
	}
	free (temp);
	return (data_read);
}

char	*ft_write_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_next_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (NULL);
	}
	line = malloc((ft_strlen(buffer) - i) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free (buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_write_line (buffer[fd]);
	buffer[fd] = ft_next_line (buffer[fd]);
	return (line);
}
/*
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <archivo1> [archivo2 ...]\n", argv[0]);
        return (1);
    }

    // Abrimos todos los archivos especificados como argumentos
    int *fds = malloc((argc - 1) * sizeof(int));
    if (!fds)
    {
        perror("Error al reservar memoria para descriptores de archivo");
        return (1);
    }

    for (int i = 1; i < argc; i++)
    {
        fds[i - 1] = open(argv[i], O_RDONLY);
        if (fds[i - 1] < 0)
        {
            perror("Error al abrir un archivo");
            // Cerramos cualquier archivo abierto antes de salir
            for (int j = 0; j < i - 1; j++)
                close(fds[j]);
            free(fds);
            return (1);
        }
    }

    // Leemos líneas alternando entre los archivos
    int active_fds = argc - 1;
    char *line;
    while (active_fds > 0)
    {
        for (int i = 0; i < argc - 1; i++)
        {
            if (fds[i] < 0) // Si este FD ya fue cerrado, lo saltamos
                continue;

            line = get_next_line(fds[i]);
            if (line)
            {
                printf("Archivo %d (%s): %s", i + 1, argv[i + 1], line);
                free(line);
            }
            else
            {
                // Cerramos el FD si llegamos al final del archivo o hubo error
                close(fds[i]);
                fds[i] = -1; // Marcamos el FD como cerrado
                active_fds--;
            }
        }
    }

    // Liberamos memoria y salimos
    free(fds);
    return (0);
}*/