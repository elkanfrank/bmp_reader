// -------------- BMP READER ----------------- 
// TODO: Reverse pixel array? and make it faster

#include "bmp.h"

t_pixel				*read_bmp(int fd)
{
	t_bmp_header header;
	t_bmp_info info;
	t_pixel *pixels;
	uint32_t pixels_to_read;
	BYTE swap;

	// t_bmp bmp;

	read(fd, &header, sizeof(t_bmp_header));
	if (header.signature != 0x4D42)
		exit_with_error("Error: not a bmp file.\n");

	read(fd, &info, sizeof(t_bmp_info));
	if (info.bits_per_pixel != 24)
		exit_with_error("Error: only supports 24bit bmp.\n");
	print_meta_data(info);
	
	pixels_to_read = info.width * info.height;
	pixels = ft_memalloc(info.width * info.height * sizeof(t_pixel));
	while (pixels_to_read > 0){
		read(fd, &pixels[pixels_to_read - 1], info.bits_per_pixel / 8);
		swap = pixels[pixels_to_read - 1].blue;
		pixels[pixels_to_read - 1].blue = pixels[pixels_to_read - 1].red;
		pixels[pixels_to_read - 1].red = swap;
		pixels_to_read--;
	}

	printf("size: %u\n", info.img_size);
	int i = 0;
	while (i < (info.img_size / 3)){
		print_pixel(pixels[i]);
		i++;
	}

	void *init = mlx_init();
	void *window = mlx_new_window(init, 600, 400, "fdf");
	int j = 0;
	int h = 0;
	int p;

	while (j < info.width * info.height){
		p = 0;
		p = pixels[j].blue | (pixels[j].green << 8) | (pixels[j].red << 16);
		if (j != 0 && j % info.width == 0)
			h++;
		mlx_pixel_put(init, window, j % info.width, h, p);
		j++;
	}
	mlx_loop(init);
	return pixels;
}

int					main(int argc, char **argv)
{
	int				fd;
	t_bmp_header	bmp_header;
	t_pixel			*pixels;

	if (argc < 2)
		exit_with_error("Usage: ./bmp_reader [ file ]\n");

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_error("Error: invalid file descriptor\n");
	
	pixels = read_bmp(fd);
	

	return (0);
}
