#include<stdio.h>
void main()
{
	unsigned int num,pos1,inter,pos2,temp,fshift,sshift;
	printf("ENTER YOUR NUMBER ");
	scanf("%d",&num);
	printf("ENTER THE POSITIONS YOU WANT TO SWAP ");
	scanf("%u%u",&pos1,&pos2);
	fshift=(num>>pos1)&1;
	
	sshift=(num>>pos2)&1;
	
	temp=fshift^sshift;
	
	inter=(temp<<pos1)|(temp<<pos2);
	num=num^inter;
	printf("NUMBER IS =%u\n",num);



}
