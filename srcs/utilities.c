#include "bmp.h"

void				print_bytes(BYTE *bytes, unsigned int len)
{
	BYTE* temp;

	temp = bytes;
	while (len > 0){
		printf("%u ", *temp++);
		len--;
	}
	printf("\n");
}

void				exit_with_error(const char *message){
	ft_putstr_fd(message, 2);
	exit(1);
}

unsigned int		uint32_sub_abs(unsigned int a, unsigned int b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}

unsigned char		*ft_bytejoin(BYTE *s1, BYTE *s2, unsigned int bytes_read)
{
	BYTE *fresh;
	BYTE *temp;

	fresh = (BYTE *)malloc(bytes_read);
	temp = fresh;
	if (!fresh)
		return (NULL);
	if (s1){
		ft_memcpy(temp, s1, bytes_read - 1);
		temp += bytes_read - 1;
		ft_memcpy(temp, s2, 1);
	}
	else
		ft_memcpy(temp, s2, 1);
	return (fresh);
}

void		print_meta_data(t_bmp_info info)
{
	printf("info size : %u\n", info.info_size);
	printf("img size  : %u\n", info.img_size);
	printf("height    : %u\n", info.height);
	printf("width     : %u\n", info.width);
	printf("bpp       : %u\n", info.bits_per_pixel);
}

void				print_pixel(t_pixel pixel)
{
	printf("( %u ", (unsigned int)pixel.red);
	printf("%u ", (unsigned int)pixel.green);
	printf("%u )", (unsigned int)pixel.blue);
}

unsigned int		bits32_to_int(BYTE bytes[])
{
	int				shift;
	unsigned int	result;

	shift = 24;
	result = 0;
	bytes += 3;
	while (shift >= 0){
		result |= (*bytes) << shift;
		shift -= 8;
		bytes--;
	}
	return result;
}

unsigned int		bits16_to_int(BYTE bytes[])
{
	int				shift;
	unsigned int	result;

	shift = 16;
	result = 0;
	bytes += 1;
	while (shift >= 0){
		result |= (*bytes) << shift;
		shift -= 8;
		bytes--;
	}
	return result;
}
