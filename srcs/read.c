// -------------- BMP READER ----------------- 

#include "bmp.h"

static void			read_pixels(t_bmp *bmp, int fd)
{
	uint8_t			swap;
	uint8_t			padding;
	uint8_t			temp[4];
	uint32_t 		i;
	uint32_t		pixels_to_read;

	i = 0;
	padding = ((bmp->info.width * 3) % 4);
	if (padding)
		padding = 4 - padding;
	pixels_to_read = bmp->info.width * bmp->info.height;
	printf("padding: %u\n", padding);
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
	t_bmp			bmp;

	read(fd, &header, sizeof(t_bmp_header));
	if (header.signature != 0x4D42)
		exit_with_error("Error: not a bmp file.\n");
	read(fd, &(bmp.info), sizeof(t_bmp_info));
	if (bmp.info.bits_per_pixel != 24)
		exit_with_error("Error: only supports 24bit bmp.\n");
	bmp.pixels = ft_memalloc(bmp.info.width * bmp.info.height * sizeof(t_pixel));
	read_pixels(&bmp, fd);
	return bmp;
}
