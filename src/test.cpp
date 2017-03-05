#include <iostream>
#include <fstream>
#include <string>
#include "../libraw/libraw/libraw.h"
#include <thread>

using namespace std;

int main()
{
	string file1 = "Sigma DP1 Quattro.x3f";
	string file2 = "Sigma DP2 Quattro.x3f";

	thread one(getThumb, file1);
	thread two(getThumb, file2);

	one.join();
	two.join();
}

void getThumb(string file)
{
	LibRaw rawProcessor;
	rawProcessor.open_file(file.c_str);

	unsigned char* jpeg = NULL;
	unsigned long jpegSize = 0;

	int result = rawProcessor.unpack_thumb();
	if (result != LIBRAW_SUCCESS)
	{
		cout << libraw_strerror(result);
	}

	libraw_processed_image_t *image = rawProcessor.dcraw_make_mem_thumb(&result);
	if (result != LIBRAW_SUCCESS)
	{
		cout << libraw_strerror(result);
	}

	ofstream outFile(file + "jpg", std::ofstream::binary);
	outFile.write((char *)image->data, image->data_size);

	rawProcessor.dcraw_clear_mem(image);
}
