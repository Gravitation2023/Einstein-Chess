#include<easyx.h>
#include<math.h>
#include"Game.h"


using namespace std;


int main()
{
	bool gamestart = false;
	bool red =true;
	bool blue=true;
	startup(gamestart, red, blue);
	
	while (1)
	{
		show(gamestart, red, blue);
	}
	

	return 0;
}