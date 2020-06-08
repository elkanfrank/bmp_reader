// -------------- BMP READER ----------------- 

#include "bmp.h"

void				read_pixels(uint32_t pixels_to_read, t_bmp *bmp, int fd)
{
	BYTE			swap;
	uint8_t			padding;
	uint8_t			temp[4];
	uint32_t 		i;

	i = 0;
	padding = 4 - ((bmp->info.width * 3) % 4);
	while (i < pixels_to_read){
		if (padding && i && i % bmp->info.width == 0)
			read(fd, temp, padding);
		read(fd, &bmp->pixels[i], bmp->info.bits_per_pixel / 8);
		swap = bmp->pixels[i].blue;
		bmp->pixels[i].blue = bmp->pixels[i].red;
		bmp->pixels[i].red = swap;
		print_pixel(bmp->pixels[i]);
		i++;
	}
	return ;
}

t_bmp				read_bmp(int fd)
{
	t_bmp_header 	header;
	uint32_t 		pixels_to_read;
	t_bmp			bmp;

	read(fd, &header, sizeof(t_bmp_header));
	if (header.signature != 0x4D42)
		exit_with_error("Error: not a bmp file.\n");
	read(fd, &(bmp.info), sizeof(t_bmp_info));
	if (bmp.info.bits_per_pixel != 24)
		exit_with_error("Error: only supports 24bit bmp.\n");
	pixels_to_read = bmp.info.width * bmp.info.height;
	bmp.pixels = ft_memalloc(bmp.info.width * bmp.info.height * sizeof(t_pixel));
	read_pixels(pixels_to_read, &bmp, fd);

	void *init = mlx_init();
	void *window = mlx_new_window(init, 600, 400, "fdf");
	int j = 0;
	int h = 0;
	int p;

	while (j < bmp.info.width * bmp.info.height){
		p = 0;
		p = bmp.pixels[j].blue | (bmp.pixels[j].green << 8) | (bmp.pixels[j].red << 16);
		if (j != 0 && j % bmp.info.width == 0)
			h++;
		mlx_pixel_put(init, window, j % bmp.info.width, h, p);
		j++;
	}
	mlx_loop(init);
	return bmp;
}

int					main(int argc, char **argv)
{
	int				fd;
	t_bmp			bmp;

	if (argc < 2)
		exit_with_error("Usage: ./bmp_reader [ file ]\n");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_with_error("Error: invalid file descriptor\n");
	bmp = read_bmp(fd);
	return (0);
}
