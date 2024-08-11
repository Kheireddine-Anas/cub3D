#include "../cub3d.h"

void erroring(int err) {
    if (err == 1)
        printf("Error\nCheck the number of args\n");
    exit(1);
}

void check_extenstion(char *exe, int ac) {
    int i = 0;

    if (ac != 2)
        erroring(1);
    while (exe[i])
        i++;
    if (!(exe[i - 5]) || exe[i - 4] != '.' || exe[i - 3] != 'c'
        || exe[i - 2] != 'u' || exe[i - 1] != 'b') {
        write(1, "Error\n", 7);
        write(1, "Map Extention Map.cub\n", 23);
        exit(1);
    }
}

void parse_rgb(char *line, int *color) {
    char **values = ft_split(line, ','); // Assuming you have implemented this function
    if (!values || !values[0] || !values[1] || !values[2]) {
        printf("Error\nInvalid RGB values\n");
        exit(1);
    }
    color[0] = atoi(values[0]);
    color[1] = atoi(values[1]);
    color[2] = atoi(values[2]);
    for (int i = 0; values[i]; i++)
        free(values[i]);
    free(values);
}

void parse_cub_file(char *filename, t_config *config) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        if (strncmp(line, "NO ", 3) == 0)
            config->north_texture = strdup(line + 3);
        else if (strncmp(line, "SO ", 3) == 0)
            config->south_texture = strdup(line + 3);
        else if (strncmp(line, "WE ", 3) == 0)
            config->west_texture = strdup(line + 3);
        else if (strncmp(line, "EA ", 3) == 0)
            config->east_texture = strdup(line + 3);
        else if (strncmp(line, "F ", 2) == 0)
            parse_rgb(line + 2, config->floor_color);
        else if (strncmp(line, "C ", 2) == 0)
            parse_rgb(line + 2, config->ceiling_color);
        free(line);
    }
    close(fd);
}

int main(int ac, char **av) {
    t_config config = {0};
    check_extenstion(av[1], ac);
    parse_cub_file(av[1], &config);
    
    // Now you can use the config structure with the parsed values
    printf("North Texture: %s\n", config.north_texture);
    printf("South Texture: %s\n", config.south_texture);
    printf("West Texture: %s\n", config.west_texture);
    printf("East Texture: %s\n", config.east_texture);
    printf("Floor Color: %d, %d, %d\n", config.floor_color[0], config.floor_color[1], config.floor_color[2]);
    printf("Ceiling Color: %d, %d, %d\n", config.ceiling_color[0], config.ceiling_color[1], config.ceiling_color[2]);
    
    // Remember to free allocated memory
    free(config.north_texture);
    free(config.south_texture);
    free(config.west_texture);
    free(config.east_texture);
    
    return 0;
}
