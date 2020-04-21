#include "mbed.h"
#include "C12832_lcd.h"
#include "Small_7.h"
#include "graphics.h"
#ifndef functionlist_H
#define functionlist_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
C12832_LCD lcd;
BusIn joy(p15,p12,p13,p16);
DigitalIn fire(p14);
int partcount = strt;
int y[total]; // y axis
int x[total]; // x axis
int yadd[total];
int xadd[total];
int add[total];
int dir[total]; // direction, 0 = right, 1 = down, 2 = left, 3 = up
bool eat[total];
int food = 0;
int OccupiedSpaces[256];
int UnoccupiedSpaces[256];
int count = 0;
int RNG = 0;
int head1 = 0;
int head2 = 0;
bool mouth = 0;



void line (int num, int pos, int xdisplace, int ydisplace)
{
	if (num == 1)
	{
		lcd.print_bm(bitmOneLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmOneLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmOneLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
	else if (num == 2)
	{
		lcd.print_bm(bitmTwoLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmTwoLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmTwoLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
	else if (num == 3)
	{
		lcd.print_bm(bitmThreeLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmThreeLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmThreeLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
	else if (num == 4)
	{
		lcd.print_bm(bitmFourLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmFourLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmFourLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
	else if (num == 5)
	{
		lcd.print_bm(bitmFiveLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmFiveLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmFiveLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
	else if (num == 6)
	{
		lcd.print_bm(bitmSixLine,x[pos]+xdisplace,y[pos]+ydisplace); lcd.print_bm(bitmSixLine,(x[pos]+xdisplace-128),y[pos]+ydisplace); lcd.print_bm(bitmSixLine,(x[pos]+xdisplace),y[pos]+ydisplace-32);
	}
}

void line (int num, int xdisplace, int ydisplace)
{
	if (num == 1)
	{
		lcd.print_bm(bitmOneLine,xdisplace,ydisplace); lcd.print_bm(bitmOneLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmOneLine,(xdisplace),ydisplace-32);
	}
	else if (num == 2)
	{
		lcd.print_bm(bitmTwoLine,xdisplace,ydisplace); lcd.print_bm(bitmTwoLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmTwoLine,(xdisplace),ydisplace-32);
	}
	else if (num == 3)
	{
		lcd.print_bm(bitmThreeLine,xdisplace,ydisplace); lcd.print_bm(bitmThreeLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmThreeLine,(xdisplace),ydisplace-32);
	}
	else if (num == 4)
	{
		lcd.print_bm(bitmFourLine,xdisplace,ydisplace); lcd.print_bm(bitmFourLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmFourLine,(xdisplace),ydisplace-32);
	}
	else if (num == 5)
	{
		lcd.print_bm(bitmFiveLine,xdisplace,ydisplace); lcd.print_bm(bitmFiveLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmFiveLine,(xdisplace),ydisplace-32);
	}
	else if (num == 6)
	{
		lcd.print_bm(bitmSixLine,xdisplace,ydisplace); lcd.print_bm(bitmSixLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmSixLine,(xdisplace),ydisplace-32);
	}
	else if (num == 7)
	{
		lcd.print_bm(bitmSevenLine,xdisplace,ydisplace); lcd.print_bm(bitmSevenLine,(xdisplace-128),ydisplace); lcd.print_bm(bitmSevenLine,(xdisplace),ydisplace-32);
	}
}
void CalcOccPos(int x, int y, int num)
{
	if(y%4 == 0)
	{
		if (num == 0)
		{
			OccupiedSpaces[( (x-2)/4 + (y/4)*32 )] = 1;
		}
		else if (num == 1)
		{
			if ( ( (x-2)/4 + (y/4)*32 )%32 == 31 )
			{
				OccupiedSpaces[( (x-2)/4 + (y/4)*32 )-31]= 1;
			}
			else 
			{
				OccupiedSpaces[( (x-2)/4 + (y/4)*32 )+1] = 1;
			}
		}
	}
	else 
	{
		if (num == 0)
		{
			OccupiedSpaces[( x/4 + ((y-2)/4)*32 )] = 1;
		}   
		else if (num == 1)
		{
			if ( ( x/4 + ((y-2)/4)*32 )/32 == 7)
			{
				OccupiedSpaces[( x/4 + ((y-2)/4)*32 )-224] = 1;
			}
			else 
			{
				OccupiedSpaces[( x/4 + ((y-2)/4)*32 )+32] = 1;
			}
		}
	}
}
int CountOccPos()
{
	count = 0;
	int count2 = 0;
	for (int i = 0; i<256; i++)
	{
		if (OccupiedSpaces[i] == 1) count++;
		else 
		{
			UnoccupiedSpaces[count2] = i;
			count2++;
		}
	}
	return count2;
}
void randomise()
{
	for (int i = 0; i < partcount; i++)
	{
		CalcOccPos(x[i],y[i],0);
		CalcOccPos(x[i],y[i],1);
	}
	food = rand()%(CountOccPos());
}
void initialise()
{
	for (int i = 0; i < 256; i++)
	{
		OccupiedSpaces[i] = 0;
		UnoccupiedSpaces[i] = 0;
		eat[i] = 0;
	}
	
	partcount = strt;
	srand(RNG);
	for (int i = 0; i < total; ++i) // Initialise variables
	{
		yadd[i] = 0;
		dir[i] = 0;
		if (i<(partcount))
		{
			xadd[i] = 4;
			x[i] = ((partcount-i-1)*4+2);
			y[i] = 0;              
		}              
		else {xadd[i] = 0;x[i] = ((partcount-i-1)*4+2); y[i] = 0; dir[i] = 0;}
	}

	randomise();   
}



void tailbox(int pos, int dirc)
{
	if (dirc == 0)
	{
		if (dir[pos-1] == 3)line(3,pos,0,1);
		else line(4,pos,0,1);
		if (dir[pos-1] == 3)line(6,pos,-2,2);
		else line(5,pos,-2,2);
	}
	else if (dirc ==1)
	{
		line(1,pos,2,-2);
		line(1,pos,2,-1);
		line(2,pos,1,0);
		line(2,pos,1,1);
		line(2,pos,1,2);
		if (dir[pos-1] == 2)line(1,pos,1,3);
		else line(1,pos,2,3);
	}
	else if (dirc==2)
	{
		if (dir[pos-1] == 3)line(3,pos,1,1);
		else line(4,pos,0,1);
		if (dir[pos-1] == 3) line(6,pos,0,2);
		else line(5,pos,1,2);
	}
	else if (dirc==3)
	{
		if (dir[pos-1] == 2)line(1,pos,2,0);
		else line(1,pos,1,0);
		line(2,pos,1,1);
		line(2,pos,1,2);
		line(2,pos,1,3);
		line(1,pos,2,4);
		line(1,pos,2,5);
	}  
}
void bodybox(int pos, int dirc)
{
	if (dirc == 0)
	{
		if (eat[pos] == 1)
		{
			line(2,pos,-1,0);
			line(2,pos,-1,3);
		}
		if (dir[pos+1] == 3)line(2,pos,0,1);
		else line(1,pos,1,1);
		if (dir[pos-1] == 3)line(1,pos,2,1);
		else line(2,pos,2,1);
		if (dir[pos+1] == 3)line(1,pos,1,2);
		else line(2,pos,0,2);
		if (dir[pos-1] == 3)line(2,pos,2,2);
		else line(1,pos,2,2);
	}
	else if (dirc ==1)
	{
		if (eat[pos] == 1)
		{
			line(1,pos,0,3);
			line(1,pos,3,3);
			line(1,pos,0,4);
			line(1,pos,3,4);
		}
		if (dir[pos+1] == 2)line(1,pos,1,0);
		else line(1,pos,2,0);
		line(2,pos,1,1);
		line(2,pos,1,2);
		if (dir[pos-1] == 2)line(1,pos,2,3);
		else line(1,pos,1,3);
	}
	else if (dirc ==2)
	{
		if (eat[pos] == 1)
		{
			line(2,pos,3,0);
			line(2,pos,3,3);
		}
		if (dir[pos-1] == 3)line(1,pos,1,1);
		else line(2,pos,0,1);
		if (dir[pos+1] == 3)line(2,pos,2,1);
		else line(1,pos,2,1);
		if (dir[pos-1] == 3)line(2,pos,0,2);
		else line(1,pos,1,2);
		if (dir[pos+1] == 3)line(1,pos,2,2);
		else line(2,pos,2,2);
	}
	else if (dirc ==3)
	{
		if (eat[pos] == 1)
		{
			line(1,pos,0,-1);
			line(1,pos,3,-1);
			line(1,pos,0,0);
			line(1,pos,3,0);
		}
		if (dir[pos-1] == 2)line(1,pos,2,0);
		else line(1,pos,1,0);
		line(2,pos,1,1);
		line(2,pos,1,2);
		if (dir[pos+1] == 2)line(1,pos,1,3);
		else line(1,pos,2,3);
	}   
}
void headbox(int pos, int dirc)
{
	if (dirc == 0)
	{
		line(1,pos,2,0);
		if (dir[pos+1] == 3) line(2,pos,0,1);
		else line(1,pos,1,1);
		if (mouth == 0)line(2,pos,3,1);
		else if (mouth == 1) line(1,pos,3,1);
		if (dir[pos+1] == 3)
		{
			line(3,pos,1,2);
			if (mouth == 0) line(1,pos,4,2);
			else if (mouth == 1) 
			{
				line(1,pos,4,0);
				line(1,pos,4,3);
			}
		}               
		else
		{
			line(4,pos,0,2);
			if (mouth == 0) line(1,pos,4,2);
			else if (mouth == 1) 
			{
				line(1,pos,4,0);
				line(1,pos,4,3);
			}
		}               
	}
	else if (dirc ==1)
	{  
		if (dir[pos+1] == 2) line(1,pos,1,0);
		else line(1,pos,2,0);
		line(2,pos,1,1);
		line(1,pos,0,2);
		line(1,pos,2,2);
		line(2,pos,1,3);
		if (mouth == 0) line(2,pos,1,4);
		else if (mouth == 1) 
		{
			line(1,pos,0,4);
			line(1,pos,3,4);
		}
	}
	else if (dirc==2)
	{
		line(1,pos,1,0);
		if (mouth == 0)line(2,pos,-1,1);
		else if (mouth == 1)line(1,pos,0,1);
		if (dir[pos+1] == 3) line(2,pos,2,1);
		else line(1,pos,2,1);
		if (dir[pos+1] == 3)
		{
			if (mouth == 0)line(4,pos,-1,2);
			else if (mouth == 1)line(3,pos,0,2);
		}               
		else
		{
			if (mouth == 0)line(5,pos,-1,2);
			if (mouth == 1)line(4,pos,0,2);
			
		}   
		if (mouth == 1)
		{
			line(1,pos,-1,0);
			line(1,pos,-1,3);
		}
	}
	else if (dirc==3)
	{
		
		if (mouth == 0)line(2,pos,1,-1);
		else if (mouth == 1)
		{
			line(1,pos,0,-1);
			line(1,pos,3,-1);
		}
		line(2,pos,1,0);
		line(1,pos,0,1);
		line(1,pos,2,1);
		line(2,pos,1,2);
		if (dir[pos+1] == 2) line(1,pos,1,3);
		else line(1,pos,2,3);
	}   
}
void foodbox(int displace)
{
	line(1,(4*(displace%32)+1),(4*(displace/32)));
	line(1,(4*(displace%32)),(4*(displace/32)+1));
	line(1,(4*(displace%32)+2),(4*(displace/32)+1));
	line(1,(4*(displace%32)+1),(4*(displace/32)+2)); 
}

void inputdirection(int joy)
{

	if (joy==1) 
	{
		if (dir[0] != 1) dir[0] = 3;
	} // up
	else if (joy==2) 
	{
		if (dir[0] != 3) dir[0] = 1;
	} // down
	else if (joy==4) 
	{
		if (dir[0] !=0) dir[0] = 2;
	} // left
	else if (joy==8) 
	{
		if (dir[0]!=2) dir[0] = 0;
	} // right
		
}   
void calcdirection(int pos)
{
	if (dir[pos] == 0) 
	{
		if (dir[pos+1] == 3) 
		{
			xadd[pos]=2; yadd[pos]=-2;
		}
		else if (dir[pos+1] == 1) 
		{
			xadd[pos]=2; yadd[pos]=2;
		}
		else 
		{
			yadd[pos]=0; xadd[pos] = 4;
		}
	} // right
	else if (dir[pos] == 1) 
	{
		if (dir[pos+1] == 0) 
		{
			xadd[pos]=2; yadd[pos]=2;
		}
		else if (dir[pos+1] == 2) 
		{
			xadd[pos]=-2; yadd[pos]=2;
		}
		else 
		{
			yadd[pos]=4; xadd[pos] = 0;
		}
	} // down
	else if (dir[pos]==2)
	{
		if (dir[pos+1]==1)
		{
			xadd[pos]=-2;yadd[pos]=2;
		}
		else if (dir[pos+1]==3)
		{
			xadd[pos]=-2;yadd[pos]=-2;
		}
		else 
		{
			xadd[pos]=-4;yadd[pos]=0;
		}
	}
// left
	else if (dir[pos] == 3)
	{
		if(dir[pos+1]==2)
		{
			xadd[pos]=-2;yadd[pos]=-2;
		}
		else if(dir[pos+1]==0)
		{
			xadd[pos]=2;yadd[pos]=-2;
		}
		else
		{
			yadd[pos]=-4;xadd[pos]=0;
		}
	}
 // up
 }
void draw(int diff)
{
	lcd.cls();
	lcd.locate(0,20);
	lcd.printf("%d %d %d %d",eat[0], eat[1], eat[2], eat[3]);
	for(int i = (partcount-1); i>-1;i--)
	{
		if (i == (partcount-1) )
		{
			tailbox(i+diff,dir[i+diff]);
		}
		else if (i == 0)
		{
			headbox(i+diff,dir[i+diff]); 
		}
		else 
		{
			bodybox(i+diff,dir[i+diff]);        
		}
	}
	
	foodbox(UnoccupiedSpaces[food]);
	
	lcd.copy_to_lcd();
}
void increase()
{
	partcount++;
	eat[0] = 1;  
}        
void gameover(int diff)
{
	for(int i = 0; i<3; i++)
	{
		draw(diff);
		wait(0.2);
		lcd.cls();
		wait(0.2);
		
	}
	lcd.cls();  
	 line(3,39,12); line(2,91,12); line(2,38,13); line(2,91,13); line(2,38,14); line(3,45,14); line(7,50,14); line(3,60,14); line(3,69,14); line(2,74,14); line(2,77,14); line(3,81,14); line(2,86,14); line(1,89,14); line(2,91,14); line(2,38,15); line(2,41,15); line(2,47,15); line(2,50,15); line(2,53,15); line(2,56,15); line(2,59,15); line(2,62,15); line(2,68,15); line(2,71,15); line(2,74,15); line(2,77,15); line(2,80,15); line(2,83,15); line(4,86,15); line(2,91,15); line(2,38,16); line(2,41,16); line(4,45,16); line(2,50,16); line(2,53,16); line(2,56,16); line(5,59,16); line(2,68,16); line(2,71,16); line(3,75,16); line(5,80,16); line(2,86,16); line(2,91,16); line(2,38,17); line(2,41,17); line(2,44,17); line(2,47,17); line(2,50,17); line(2,53,17); line(2,56,17); line(2,59,17); line(2,68,17); line(2,71,17); line(3,75,17); line(2,80,17); line(2,86,17); line(0,39,12); line(4,39,18); line(4,45,18); line(2,50,18); line(2,53,18); line(2,56,18); line(4,60,18); line(3,69,18); line(1,76,18); line(4,81,18); line(2,86,18); line(2,91,18);
	 lcd.copy_to_lcd();
	 wait(2);
	initialise();
}  

void checkforloss()
{
	if (dir[0] == 0)
	{
		for(int i = 1;i<(partcount);i++)
		{
			if ( (x[0] == x[i]-2 || x[0] == x[i]+126)  &&  ( y[0] == y[i] -2 || y[0] == y[i] +30  || y[0] == y[i] + 2) ) gameover(1);
			else if ( (x[0] == x[i]-8 || x[0] == x[i] + 120) && y[0] == y[i] && (i == partcount-1)) gameover(0);
		}
	}
	else if (dir[0] == 1)
	{
		for(int i = 1;i<(partcount);i++)
		{
			if ( (x[0] ==x[i] + 2 || x[0] == x[i]-2 || x[0] == x[i]+126) && (y[0] == y[i] -2 || y[0] == y[i] +30 ) )gameover(1);
			else if ( (y[0] == y[i]-8||y[0] == y[i]+24 ) && x[0] == x[i]&& (i == partcount-1)) gameover(0);
		}
	}
	else if (dir[0] == 2)
	{
		for(int i = 1;i<(partcount);i++)
		{
			if (x[0] ==x [i] +2  &&  (y[0] == y[i] -2 || y[0] == y[i] +30  || y[0] == y[i] + 2) )gameover(1);
			else if ( (x[0] == x[i]+8 || x[0] == x[i] - 120 ) && y[0] == y[i]&& (i == partcount-1)) gameover(0);
		}
	}
	else if (dir[0] == 3)
	{
		for(int i = 1;i<(partcount);i++)
		{
			if ( (x[0] == x[i] + 2 || x[0] == x[i] - 2 || x[0] == x[i]+126) && y[0] == y[i] +2 )gameover(1);
			else if ( (y[0] == y[i]+8 || y[0] == y[i]-24) && x[0] == x[i]&& (i == partcount-1)) gameover(0);
		}
	}
	
}
void checkforfood()
{
	head1 = 0;
	head2 = 0;
	if(y[0]%4 == 0)
	{
		head1 =  (x[0]-2)/4 + (y[0]/4)*32 ;
			if ( ( (x[0]-2)/4 + (y[0]/4)*32 )%32 == 31 )
			{
				head2 = (x[0]-2)/4 + (y[0]/4)*32 -31;
			}
			else 
			{
				head2 =  (x[0]-2)/4 + (y[0]/4)*32 +1;
			}
	}
	else 
	{
		head1 =( x[0]/4 + ((y[0]-2)/4)*32 );
		if ( ( x[0]/4 + ((y[0]-2)/4)*32 )/32 == 7)
		{
			head2 =  x[0]/4 + ((y[0]-2)/4)*32 -224;
		}
		else 
		{
			head2 = x[0]/4 + ((y[0]-2)/4)*32 +32;
		}
		
	}
	
	if ( head1 == UnoccupiedSpaces[food] || head2 == UnoccupiedSpaces[food] )
	{
		increase();
		randomise();
	}

	if (dir[0] == 0)
	{
		if (UnoccupiedSpaces[food]%32 == 0)
		{
			if(head2 == UnoccupiedSpaces[food] + 31) mouth = 1;
			else mouth = 0;
		}
		else if(head2 == UnoccupiedSpaces[food] - 1) mouth = 1;
		else mouth = 0;
	}           
	else if (dir[0] == 1)
	{
		if (UnoccupiedSpaces[food]/32 == 0)
		{
			if(head2 == UnoccupiedSpaces[food] + 224) mouth = 1;
			else mouth = 0;
		}
		else if(head2 == UnoccupiedSpaces[food] - 32) mouth = 1;
		else mouth = 0;
	}           
	else if (dir[0] == 2)
	{
		if (UnoccupiedSpaces[food]%32 == 31)
		{
			if(head2 == UnoccupiedSpaces[food] - 31) mouth = 1;
			else mouth = 0;
		}
		else if(head1 == UnoccupiedSpaces[food] + 1) mouth = 1;
		else mouth = 0;
	}           
	else if (dir[0] == 3)
	{
		if (UnoccupiedSpaces[food]/32 == 7)
		{
			if(head2 == UnoccupiedSpaces[food] - 224) mouth = 1;
			else mouth = 0;
		}
		else if(head1 == UnoccupiedSpaces[food] + 32) mouth = 1;
		else mouth = 0;
	}           
	
}


#endif
