#ifndef _EXITPOINT_H_
#define _EXITPOINT_H_
#include "ExitPoint.h"
#include "io_utils.h"
using namespace std;

typedef struct
{
	int x;
	int y;
}ExitPoint_location_t;

/*typedef struct
{
	int size_lines;
	int size_columns;
}ExitPoint_size_t;*/

class ExitPoint
{
private:
	ExitPoint_location_t location;
	//ExitPoint_size_t size;
public:
	ExitPoint(ExitPoint_location_t exitpoint_start_location)
	{
		//size = exitpoint_size;
		location = exitpoint_start_location;
	};

	void Draw()
	{
		gotoxy(location.x, location.y);
		cout << "X";
	};
};
#endif