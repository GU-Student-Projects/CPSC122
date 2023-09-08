#include "count.h"

bool openInputFile(ifstream &infile, string filename)
{
	infile.open(filename);

	if (infile.is_open())
	{
		return true;
	}
	return false;
}