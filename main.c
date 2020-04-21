#define total 256
#define strt 5
#define speed 0.9
#include "mbed.h"
#include "C12832_lcd.h"
#include "Small_7.h"
#include "graphics.h"
#include "functionlist.h"




int main()
{
	int counter =0;
	while (counter <1)
	{
		if (fire) counter = 1;
		RNG++;
		wait(0.1);
	}
	initialise();
	while(1)
	{
		
		draw(0);
		wait(speed);
		
		
		for(int i = (total-1);i>0;i--)
		{
			dir[i] = dir[i-1];
		}
		for (int i = (total-1); i>0; i--)
		{
			eat[i] = eat[i-1];
		}
		eat[0] = 0;
		inputdirection(joy);
		for (int i = 0; i < total; ++i) 
		{
			calcdirection(i);
		}


		for(int i = 0;i<(total);i++)
		{
			x[i]+=xadd[i]; 
		}

		for(int i = 0;i<(total);i++)
		{
			x[i] = (128+x[i])%128;
		}
		
		
		for(int i = 0;i<(total);i++)
		{
			y[i]+=yadd[i];     
		}
		
			for(int i = 0;i<(total);i++)
		{
			y[i] = (32+y[i])%32;
		}
		 checkforloss();
		 checkforfood();
		if (fire)
		{
			eat[0] = 1;
		}

		  
	} // close bracket of infinite while loop

   
}
	
	
