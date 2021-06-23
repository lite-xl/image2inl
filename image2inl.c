// Coverts a supported image file to an RGBA array
// To compile: gcc -lm -o image2inl image2inl.c
//
// Used as a base:
// https://wiki.wxwidgets.org/Embedding_PNG_Images-Bin2c_In_C
//
// STB header library:
// https://github.com/nothings/stb
//
// And stb sample code from:
// https://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void help(void) {
	fprintf(stderr, "Usage: image2inl <input_file> <output_file>\n");
	exit(1);
}

void convert(const char *ifname, const char *ofname) {
	// Check if input file exists
	FILE *ifile, *ofile;
	ifile = fopen(ifname, "rb");
	if (ifile == NULL) {
		fprintf(stderr, "cannot open %s for reading\n", ifname);
		exit(1);
	}
	fclose(ifile);

	// Check if output location is writable
	ofile = fopen(ofname, "wb");
	if (ofile == NULL) {
		fprintf(stderr, "cannot open %s for writing\n", ofname);
		exit(1);
	}

	// Write output
	fprintf(ofile, "static unsigned char icon_rgba[] = {\n");

	// use STBI_rgb if you don't want/need the alpha channel or STBI_rgb_alpha
	int req_format = STBI_rgb_alpha;
	int width, height, orig_format;
	unsigned char* data = stbi_load(
		ifname, &width, &height, &orig_format, req_format
	);

	if(data == NULL) {
		printf("Loading image data failed: %s", stbi_failure_reason());
		exit(1);
	}

	int c, col = 1, inc=0, size=(width*height)*4;
	while (inc < size) {
		c = data[inc];
		if(col >= 78 - 6) {
			fputc('\n', ofile);
			col = 1;
		}
		if(col == 1) {
			fprintf(ofile, "  ");
		}
		fprintf(ofile, "0x%.2x, ", c);
		col += 6;
		inc++;
	}
	fprintf(ofile, "\n};\n");
	fprintf(ofile, "static unsigned int icon_rgba_len = %d;\n", size);

	fclose(ofile);

	printf("Written %d bytes.\n", size);
}

int main(int argc, char **argv) {
	if(argc != 3) {
		help();
	}
	convert(argv[1], argv[2]);
	return 0;
}
