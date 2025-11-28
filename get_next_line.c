/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piprieto <piprieto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:36:04 by piprieto          #+#    #+#             */
/*   Updated: 2024/12/17 12:25:06 by piprieto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_read(char *buffer, char *temp, int byte_read)
{
	char	*new_buffer;

	if (byte_read <= 0)
		return (buffer);
	temp[byte_read] = '\0';
	new_buffer = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

char	*read_file(int fd, char *data_read)
{
	char	*temp;
	int		byte_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(data_read, '\n'))
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp);
			free(data_read);
			return (NULL);
		}
		data_read = ft_free_read(data_read, temp, byte_read);
	}
	free(temp);
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
	line = malloc((ft_strlen((const char *)buffer) - i) * sizeof(char));
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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc (1);
		if (!buffer)
		{
			free (buffer);
			return (NULL);
		}
		buffer[0] = '\0';
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_write_line (buffer);
	buffer = ft_next_line (buffer);
	return (line);
}
/*
int main(void)
{
    int fd;             // Descriptor del archivo
    char *line;         // Línea leída con get_next_line

    // Abre el archivo en modo solo lectura
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el archivo");
        return (1);
    }
    // Llama a get_next_line en un bucle y muestra cada línea
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Libera la memoria de la línea leída
    }
    // Cierra el archivo
    close(fd);
    return (0);
}*/
/*
void test_get_next_line(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error abriendo el archivo");
        return;
    }

    printf("=== Probando archivo: %s ===\n", filename);
    char *line = get_next_line(fd);
    while (line)
    {
        printf("Línea: %s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    printf("=== Fin de prueba para: %s ===\n\n", filename);
}
int main(void)
{
    // Caso 1: Archivo normal con varias líneas
    test_get_next_line("test.txt");

    // Caso 2: Archivo vacío
    test_get_next_line("vacio.txt");

    // Caso 3: Archivo sin saltos de línea
    test_get_next_line("testsinsalto.txt");

    // Caso 4: Archivo con un único salto de línea
    test_get_next_line("testunsalto.txt");

    // Caso 5: Descriptor de archivo inválido
    printf("=== Probando descriptor de archivo inválido ===\n");
    char *line = get_next_line(-1);
    if (!line)
        printf("Resultado esperado: NULL para descriptor inválido.\n");
    free(line);

    return 0;
}*/