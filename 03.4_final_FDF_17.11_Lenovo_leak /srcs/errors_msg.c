#include "fdf.h"
/*
//plus besoin
void exit_error_msg(char *error_message)
{
    ft_printf("%s\n", error_message);  // !!! changer en ft_printf
    exit(EXIT_FAILURE);
}

void error_msg(char *error_message)
{
    printf("%s\n", error_message);  // !!! changer en ft_printf
}

// nouvealle focntion remplace exit_error_msg
void exit_with_err(const char *error_type) 
{
    printf("%s: %s\n", error_type, strerror(errno)); // Utilisation de printf au lieu de fprintf
    exit(EXIT_FAILURE);
}
*/

void print_error_and_exit(const char *type, int use_errno)
{
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd((char *)type, 2);
    if (use_errno)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
    }
    ft_putstr_fd("\n", 2);
    exit(EXIT_FAILURE);
}

void print_error_without_exit(const char *type, int use_errno)
{
    ft_putstr_fd("Error: ", 2);// Writes "Error: " to stderr
    ft_putstr_fd((char *)type, 2);// Writes custom message to stderr
    if (use_errno) {// If use_errno is non-zero (e.g., 1)
        ft_putstr_fd(": ", 2);// Adds a separator
        ft_putstr_fd(strerror(errno), 2);// Writes system error message
    }
    ft_putstr_fd("\n", 2);// Adds a newline
}

/* ci dessous exit_utils.c*/

int	shutdown_fdf(t_display *display)
{
	free_all_struct_display(display);
	ft_printf("FdF closed cleanly\n");
	exit (EXIT_SUCCESS);
}
// remarque fait la meme chose que en haut
int win_exit_and_cleanup(t_display *dispay)
{
    free_all_struct_display(dispay);
    ft_printf("Sturny's FdF was closed succefully\n");
    exit (EXIT_SUCCESS);
    return (0);
}

/* ci dessous memory.c*/

/*
// ok verirife
libre la mémoire allouée pour la map
verifie si la map est NULL (valide)
libere chaque element denas les tableaux 2d z_ij et color et cela ligne par ligne
libere les tableau eux meme
libere la structure map

*/

void free_map_memory(t_map *map)
{
	int i;

	if (map == NULL) // a verifier si valide
		return ;
	if (map->z_ij) //ici verifie si z_ij est alloue: Il s'agit d'un tableau de pointeurs qui représentent les lignes de la matrice des hauteurs de la carte.
	{
		i = -1;
		while (++i < map->map_height) // parcourt cahque ligne de la matrice (tableau 1D)
		{
			if (map->z_ij[i]) // si de la memoire est allouee pour la ligne
				free(map->z_ij[i]); // libere la memoire allouee pour cahque ligne
		}
		free(map->z_ij); // libere la memoire allouee pour le tableau de pointeurs
	}
	if (map->color) //verife si tablaeu de couleurs est alloue
	{
		i = -1;
		while (++i < map->map_height) // parcourt cahque ligne 
		{
			if (map->color[i]) // si de la memoire est allouee pour la ligne
				free(map->color[i]); // libere la memoire allouee pour chaque ligne
		}
		free(map->color); // libere enfin le tableau de pointeurs
	}
	free(map); // libere la structure map en tant qu'objet global (une fois que tout les sous elements ont ete liberes)
}


void free_matrix(char **matrix)
{
	int i;

	if (!matrix)
	{
		ft_printf("Warning: Attempted to free a NULL matrix.\n");
		return;
	}

	i = 0;
	while (matrix[i])
	{
		//ft_printf("Freeing matrix[%d]: %p\n", i, (void *)matrix[i]);
		free(matrix[i]);
		i++;
	}
	//ft_printf("Freeing matrix itself: %p\n", (void *)matrix);
	free(matrix);
}
/*
// free / destroy all variable of the struct s_display ( )
void free_all_struct_display(t_display *display)
{
	int y;
	int	tmp_map_height;
	
	if (!display)
		return ;
	if (display->mlx_ptr && display->window_ptr)
		mlx_destroy_window(display->mlx_ptr, display->window_ptr);
	if (display->mlx_ptr && display->img && display->img->img_ptr)
		mlx_destroy_image(display->mlx_ptr, display->img->img_ptr);
	if (display->map)
		tmp_map_height = display->map->map_height; // Store before freeing
	free_map_memory(display->map); // Frees display->map
	if (display->img)
		free(display->img);
	if (display->transformed)
	{
		y = -1;
		while (++y < tmp_map_height)
		{
			if (display->transformed[y])
				free(display->transformed[y]);
		}
		free(display->transformed);
	}
	free(display);
}
*/

/*
void free_all_struct_display(t_display *display)
{
    int y;
    int tmp_map_height;

    if (!display)
        return;
    if (display->mlx_ptr && display->window_ptr)
        mlx_destroy_window(display->mlx_ptr, display->window_ptr);
    if (display->mlx_ptr && display->img && display->img->img_ptr)
        mlx_destroy_image(display->mlx_ptr, display->img->img_ptr);
    if (display->mlx_ptr)
    {
        mlx_destroy_display(display->mlx_ptr);
        free(display->mlx_ptr);
    }
    if (display->map)
        tmp_map_height = display->map->map_height;
    free_map_memory(display->map);
    if (display->img)
        free(display->img);
    if (display->transformed)
    {
        y = -1;
        while (++y < tmp_map_height)
            if (display->transformed[y])
                free(display->transformed[y]);
        free(display->transformed);
    }
    free(display);
}
*/

void free_all_struct_display(t_display *display)
{
    int y;
    int tmp_map_height;

    if (!display)
        return;
    if (display->mlx_ptr && display->window_ptr)
        mlx_destroy_window(display->mlx_ptr, display->window_ptr);
    if (display->mlx_ptr && display->img && display->img->img_ptr)
        mlx_destroy_image(display->mlx_ptr, display->img->img_ptr);
    if (display->mlx_ptr)
    {
        mlx_destroy_display(display->mlx_ptr);
        free(display->mlx_ptr);
        display->mlx_ptr = NULL; // Added to prevent double-free risks
    }
    if (display->map)
        tmp_map_height = display->map->map_height;
    free_map_memory(display->map);
    display->map = NULL; // Added
    if (display->img)
    {
        free(display->img);
        display->img = NULL; // Added
    }
    if (display->transformed)
    {
        y = -1;
        while (++y < tmp_map_height)
            if (display->transformed[y])
            {
                free(display->transformed[y]);
                display->transformed[y] = NULL; // Added
            }
        free(display->transformed);
        display->transformed = NULL; // Added
    }
    
    // Free the tile system
    free_tile_system(display);
    
    free(display);
    // Note: No need to set display to NULL here since it’s a local pointer
}