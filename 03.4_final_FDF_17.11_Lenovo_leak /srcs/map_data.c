/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:38 by csturny           #+#    #+#             */
/*   Updated: 2025/03/18 19:57:40 by csu-ubuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// a rervoir tout niveau compréhension.
void	ft_striter_tolower(char *str); 

// ok verrifie
void    get_map(char *file_name, t_map *map)
{
	(void)map;
	alloc_memory_for_map(map);
	stock_map_values(file_name, map);
}


// ok verifie
// a changer en calloc
// Sets up the 2D arrays for data storage. Allocation mémoir pour matrice for z_ij and for color
void    alloc_memory_for_map(t_map *map)
{
	int i;

	map->z_ij = (int **)ft_calloc(map->map_height, sizeof(int *)); // a changer en calloc
	map->color = (int **)ft_calloc(map->map_height,sizeof(int *));
	if (!map->z_ij || !map->color)
	{
		free_map_memory(map);
		print_error_and_exit("Memory allocation failed", 1);
	}
	i = -1;
	while (++i < map->map_height)
	{
		map->z_ij[i] = (int *)ft_calloc(map->map_width, sizeof(int)); 
		map->color[i] = (int *)ft_calloc(map->map_width, sizeof(int));
		if (!map->z_ij[i] ||!map->color[i])
		{
			free_map_memory(map);
			print_error_and_exit("Memory allocation failed", 1);
		}
	}
}

// ok verifie
void    stock_map_values(char *file_name, t_map *map)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		free_map_memory(map);
		print_error_and_exit("Error opening file", 1);
	}
	extract_map_data_z_color(fd, map);
	close(fd);
}
/*
// ok verifie
// a revoir ne comprend pas tout!!!!
void    extract_map_data_z_color(int fd, t_map *map) // a revoir
{
	char *line;
	char **split;
	int i;
	int j;

	i = -1;
	while (++i < map->map_height)
	{
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		if (!split)
		{
			free_map_memory(map);
			print_error_and_exit("Memory allocation failed while splitting line", 1);
		}
		j = -1;
		while (++j < map->map_width)
		{
			map->z_ij[i][j] = ft_atoi(split[j]);
			map->color[i][j] = get_color(split[j], map);
		}
		free_matrix(split);
		free(line);
	}
}
*/

void extract_map_data_z_color(int fd, t_map *map)
{
    char *line;
    char **split;
    int i;
    int j;

    i = -1;
    while (++i < map->map_height)
    {
        line = get_next_line(fd);
        if (!line) // Check for NULL to handle EOF or read errors
        {
            free_map_memory(map);
            print_error_and_exit("Unexpected end of file or read error", 1);
        }
        split = ft_split(line, ' ');
        if (!split)
        {
            free(line); // Free line before exiting
            free_map_memory(map);
            print_error_and_exit("Memory allocation failed while splitting line", 1);
        }
        j = -1;
        while (++j < map->map_width)
        {
            map->z_ij[i][j] = ft_atoi(split[j]);
            map->color[i][j] = get_color(split[j], map);
        }
        free_matrix(split);
        free(line);
    }
    // Consume any remaining get_next_line output (e.g., empty string at EOF)
    line = get_next_line(fd);
    if (line)
        free(line); // Free the leftover empty string, if any
}

// ok verife, j ai une autre implementation de ft_atoi_base!!!
int	get_color(char *str, t_map *map)
{
	while (*str && (ft_isdigit(*str) || *str == '-' || *str  == '+' || *str  == ','))
		str++;
	if (*str  && (*str  == 'x' || *str == 'X'))
	{
		map->is_color = 1;
		ft_striter_tolower(str + 1);
		return (ft_atoi_base(str + 1, 16)); // implementation differente avec 16 et pas HEXALOW
	}
	else
		return (0xFFFFFF); // a change avec une marcro
	return (0);
}

/* ci dessous map_parce.c*/

t_map *parse_map_dimensions(char *file_name)
{
    t_map *map = ft_calloc(1, sizeof(t_map));
    int fd;
    char *line;
    int width;
    
    if (!map)
		print_error_and_exit("Map is NULL", 0);
    fd = open(file_name, O_RDONLY);
    if (fd < 0) 
	{
        free(map);
		print_error_and_exit("Cannot open file", 0);
    }
    line = get_next_line(fd);
    if (!line) 
	{
        close(fd);
        free(map);
		print_error_and_exit("Empty file", 0);
    }
    map->map_width = nbr_in_a_line(map, line);
    map->map_height = 1;
    free(line);
    while ((line = get_next_line(fd))) 
	{
        // Use our improved nbr_in_a_line function for all lines
        width = nbr_in_a_line(map, line);
        free(line);
        if (width != map->map_width) {
            close(fd);
            free(map);
			print_error_and_exit("Inconsistent width", 1);
        }
        map->map_height++;
    }
    close(fd);
    //ft_printf("Map dimensions parsed: width %d, height %d\n", map->map_width, map->map_height);
    return (map);
}


/*
cette fonction compte le nombre d'éléments dans une ligne de la map
prend une ligne de la map et le nom du fichier en paramètre
decoupe en sous chaines
retourne le compte
*/
int nbr_in_a_line(t_map *map, char *line)
{
	char **split;
	int count;
	int i;

	if (!line)
	{
		free_map_memory(map);
		print_error_and_exit("Empty line in the map file (in nbr_in_a_line)", 1);
	}

	// Remove trailing newline character if present
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = '\0';

	// Remove trailing spaces
	while (i > 0 && line[i - 1] == ' ')
		line[--i] = '\0';

	split = ft_split(line, ' ');
	if (!split)
	{
		free_map_memory(map);
		print_error_and_exit("split is NULL (in nbr_in_a_line)", 1);
	}
	count = 0;
	while (split[count])
		count++;
	free_matrix(split);
	return (count);
}


// a modifier type de message d erreur!!!
void	check_file_readable(const char *filename)
{
	int fd;

	// Essayer d'ouvrir le fichier en mode lecture seule
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur"); // Affiche l'erreur avec strerror automatiquement
		exit(EXIT_FAILURE);
	}

	// Si on arrive ici, le fichier existe et est lisible
	close(fd);
}

/* ci dessous map_utils.c*/

// ok verifie
// vérifier ce que fait
// conversion des lettre majuscule en minuscule
void	ft_striter_tolower(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}


void get_z_min_max(t_map *map)
{
    int x, y;
    map->min_z = INT_MAX;
    map->max_z = INT_MIN;
    y = 0;
    while (y < map->map_height)
	{
        x = 0;
        while (x < map->map_width)
		{
            if (map->z_ij[y][x] < map->min_z)
                map->min_z = map->z_ij[y][x];
            if (map->z_ij[y][x] > map->max_z)
                map->max_z = map->z_ij[y][x];
            x++;
        }
        y++;
    }
    //ft_printf("Min z: %d, Max z: %d\n", map->min_z, map->max_z); // Debug a enlever
}

// ok verifie
int	get_abs_value(int value)
{
	if (value < 0)
		return (-(value));
	return (value);
}
