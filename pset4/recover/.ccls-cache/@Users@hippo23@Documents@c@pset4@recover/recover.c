#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

FILE *file = fopen(argv[1], "r");
typedef uint8_t BYTE;
BYTE buffer[512];
int num_jpg = 0;
char filename[] = "000.jpg";
FILE *jpeg = fopen(filename, "w");

while (fread(buffer, 1, 512, file)==512)
{
	if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
		if (num_jpg > 0)
		{
			fclose(jpeg);
			sprintf(filename, "%03i.jpg", num_jpg);
			FILE *jpeg = fopen(filename, "w");
		}
		num_jpg++;
		fwrite(buffer, 1, 512, jpeg);
	} else if (num_jpg > 0){
		fwrite(buffer, 1, sizeof(buffer), jpeg);
	}
}

fclose(file);
printf("hatdog");
}
