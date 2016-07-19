#include <bios.h>

#ifndef __GRAPHX_DEF_
#include <graphics.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

void limite(double *pvx,double *axe)
{
int answ;
double xmin,xmax,ymin,ymax,zmin,zmax;
extern int npgr;
extern double extreme[];
void recalcul(void);
void pregra(double *pva);
	char modif=0;
	printf("The extremes X are = %4g %4g ; Did you want to change them ? (y/n)\n",
			extreme[0],extreme[1]);
	answ=bioskey(0);
	if(answ==5465||answ==5497)
	{
		modif=1;
		printf("xmin xmax = ");
		scanf("%lf %lf",&xmin,&xmax);
		if(xmin>extreme[0])
		{
			xmin=extreme[0];
			printf("We have corrected xmin at %4g\n",xmin);
		}
		if(xmax<extreme[1])
		{
			xmax=extreme[1];
			printf("We have corrected xmax at %4g\n",xmax);
		}
	}
	printf("The extremes Y are = %4g %4g ; Did you want to change them ? (y/n)\n",
			extreme[2],extreme[3]);
	answ=bioskey(0);
	if(answ==5465||answ==5497)
	{
		modif=1;
		printf("ymin ymax = ");
		scanf("%lf %lf",&ymin,&ymax);
		if(ymin>extreme[2])
		{
			xmin=extreme[2];
			printf("We have corrected ymin at %4g\n",ymin);
		}
		if(ymax<extreme[3])
		{
			ymax=extreme[3];
			printf("We have corrected ymax at %4g\n",ymax);
		}
	}
	if(modif)
	{
		puts("The function was defined in the same domain.");
		puts("	1 You want to keep the original domain ");
		puts("	2 Move to the new domain");
		puts("	3 Define another domain				(1/2/3) ?");
		scanf("%d",&answ);
		switch(answ)
		{
		case 2:
			extreme[0]=xmin;
			extreme[1]=xmax;
			extreme[2]=ymin;
			extreme[3]=ymax;
			pregra(pvx);
			break;
		case 3:
			printf("Function domain on X = (%f %f) ",extreme[0],extreme[1]);
			scanf("%lf %lf",&extreme[0],&extreme[1]);
			printf("Function domain on Y = (%f %f) ",extreme[2],extreme[3]);
			scanf("%lf %lf",&extreme[2],&extreme[3]);
			pregra(pvx);
			break;
		default:
			break;
		}
		extreme[0]=xmin;
		extreme[1]=xmax;
		extreme[2]=ymin;
		extreme[3]=ymax;
	}
	printf("The extremes Z are = %4g %4g ; Did you want to change them ? (y/n)\n",
			extreme[4],extreme[5]);
	answ=bioskey(0);
	if(answ==5465||answ==5497)
	{
		printf("zmin zmax = ");
		scanf("%lf %lf",&zmin,&zmax);
		if(zmin>extreme[4])
		{
			zmin=extreme[4];
			printf("We have corrected zmin at %4g\n",zmin);
		}
		if(zmax<extreme[5])
		{
			zmax=extreme[5];
			printf("We have corrected zmax at %4g\n",zmax);
		}
		extreme[4]=zmin;
		extreme[5]=zmax;
	}
	printf("Choose the origin of X between %4g %4g; Xo = ",extreme[0],extreme[1]);
	scanf("%lf",&axe[0]);
	if(axe[0]<extreme[0])
		extreme[0]=axe[0];
	if(axe[0]>extreme[1])
		extreme[1]=axe[0];
	printf("Choose the origin of Y between %4g %4g; Yo = ",extreme[2],extreme[3]);
	scanf("%lf",&axe[1]);
	if(axe[1]<extreme[2])
		extreme[2]=axe[1];
	if(axe[1]>extreme[3])
		extreme[3]=axe[1];
	printf("Choose the origin Z between %4g %4g; Zo = ",extreme[4],extreme[5]);
	scanf("%lf",&axe[2]);
	if(axe[2]<extreme[4])
		extreme[4]=axe[2];
	if(axe[2]>extreme[5])
		extreme[5]=axe[2];
	recalcul();
	return;
}

void axele(double *d)
{
int c;
double zero[3];
void limite(double *d,double *e);
void drawaxe(double *f);
	puts("Did you want axes ? (y/n)");
	flushall();
	c=bioskey(0);
	if(c==5465||c==5497)
	{
		limite(d,zero);
		drawaxe(zero);
	}
	else
		cleardevice();
	return;
}

void drawaxe(double *axe)
{
int answx,answy,answz;
int i,nx,ny,nz;
double px,dx,pasx[32],pasy[32],pasz[32];
extern double extreme[];
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
	printf("The X axis from %4g to %4g with the origin at %4g. Divide ? (y/n)\n",
			extreme[0],extreme[1],axe[0]);
	answx=bioskey(0);
	if(answx==5465||answx==5497)
	{
		printf("division step= ");
		scanf("%lf",&dx);
		px=axe[0];
		while(px>extreme[0])
			px-=dx;
		for(nx=0;nx<32;nx++)
		{
			px+=dx;
			if(px>=extreme[1])
				break;
			pasx[nx]=px;
		}
	}
	printf("The Y axis from %4g to %4g with the origin at %4g. Divide ? (y/n)\n",
			extreme[2],extreme[3],axe[1]);
	answy=bioskey(0);
	if(answy==5465||answy==5497)
	{
		printf("division step = ");
		scanf("%lf",&dx);
		px=axe[1];
		while(px>extreme[2])
			px-=dx;
		for(ny=0;ny<32;ny++)
		{
			px+=dx;
			if(px>=extreme[3])
				break;
			pasy[ny]=px;
		}
	}
	printf("The Z axis from %4g to %4g with the origin at %4g. Divide ? (y/n)\n",
			extreme[4],extreme[5],axe[2]);
	answz=bioskey(0);
	if(answz==5465||answz==5497)
	{
		printf("division step = ");
		scanf("%lf",&dx);
		px=axe[2];
		while(px>extreme[4])
			px-=dx;
		for(nz=0;nz<32;nz++)
		{
			px+=dx;
			if(px>=extreme[5])
				break;
			pasz[nz]=px;
		}
	}
	dx=(extreme[7]-extreme[6])/639;
	double dy=extreme[9]-extreme[8];
	cleardevice();
	setcolor(15);
	moveto((horizont(extreme[0],axe[1],axe[2])-extreme[6])/dx,
			((vertical(extreme[0],axe[1],axe[2])-extreme[8])/dy-1)* -399);
	lineto((horizont(extreme[1],axe[1],axe[2])-extreme[6])/dx,
			((vertical(extreme[1],axe[1],axe[2])-extreme[8])/dy-1)* -399);
	moveto((horizont(axe[0],extreme[2],axe[2])-extreme[6])/dx,
			((vertical(axe[0],extreme[2],axe[2])-extreme[8])/dy-1)* -399);
	lineto((horizont(axe[0],extreme[3],axe[2])-extreme[6])/dx,
			((vertical(axe[0],extreme[3],axe[2])-extreme[8])/dy-1)* -399);
	moveto((horizont(axe[0],axe[1],extreme[4])-extreme[6])/dx,
			((vertical(axe[0],axe[1],extreme[4])-extreme[8])/dy-1)* -399);
	lineto((horizont(axe[0],axe[1],extreme[5])-extreme[6])/dx,
			((vertical(axe[0],axe[1],extreme[5])-extreme[8])/dy-1)* -399);
	if(answx==5465||answx==5497)
	{
		for(i=0;i<nx;i++)
		{
			moveto((horizont(pasx[i],axe[1],axe[2])-extreme[6])/dx,
					((vertical(pasx[i],axe[1],axe[2])-extreme[8])/dy-1)*-399);
			linerel(0,-3);
		}
	}
	if(answy==5465||answy==5497)
	{
		for(i=0;i<ny;i++)
		{
			moveto((horizont(axe[0],pasy[i],axe[2])-extreme[6])/dx,
					((vertical(axe[0],pasy[i],axe[2])-extreme[8])/dy-1)*-399);
			linerel(0,-3);
		}
	}
	if(answz==5465||answz==5497)
	{
		for(i=0;i<nz;i++)
		{
			moveto((horizont(axe[0],axe[1],pasz[i])-extreme[6])/dx,
					((vertical(axe[0],axe[1],pasz[i])-extreme[8])/dy-1)*-399);
			linerel(3,0);
		}
	}
	return;
}
