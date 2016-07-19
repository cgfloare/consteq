#include <bios.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <bios.h>

int npgrx,npgry,linii;
double extreme[10],xg[64],yg[64],zg[64][64],dx,dy;

void grafica(int a,double *pv)
{
void preexpp(void);
void plotexpp(void);
void funcgra(void);
void axele(double *a);
void pregra(double *a);
void erori(double *a);
void grafelim(void);
	preexpp();
	pregra(pv);
	axele(pv);
	funcgra();
	bioskey(0);
	plotexpp();
	flushall();
	a=bioskey(0);
	switch(a)
	{
	case 12386:
		erori(pv);
	case 4709:
		grafelim();
	}
	return;
}

void preexpp(void)
{
double a;
extern int npexp;
extern double extreme[],pexpx[],pexpy[],pexpz[];
	extreme[0]=extreme[1]=pexpx[0];
	extreme[2]=extreme[3]=pexpy[0];
	extreme[4]=extreme[5]=pexpz[0];
	for(int i=1;i<npexp;i++)
	{
		a=pexpx[i];
		if(extreme[0]>a)
			extreme[0]=a;
		else
			if(extreme[1]<a)
				extreme[1]=a;
		a=pexpy[i];
		if(extreme[2]>a)
			extreme[2]=a;
		else
			if(extreme[3]<a)
				extreme[3]=a;
		a=pexpz[i];
		if(extreme[4]>a)
			extreme[4]=a;
		else
			if(extreme[5]<a)
				extreme[5]=a;
	}
	return;
}

void recalcul(void)
{
int j,k;
extern double extreme[],dx,dy;
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
	extreme[6]=extreme[7]=horizont(extreme[0],extreme[2],extreme[4]);
	extreme[8]=extreme[9]=vertical(extreme[0],extreme[2],extreme[4]);
	for(int i=0;i<2;i++)
		for(j=2;j<4;j++)
			for(k=4;k<6;k++)
			{
				double h=horizont(extreme[i],extreme[j],extreme[k]);
				double v=vertical(extreme[i],extreme[j],extreme[k]);
				if(extreme[6]>h)
					extreme[6]=h;
				else
					if(extreme[7]<h)
						extreme[7]=h;
				if(extreme[8]>v)
					extreme[8]=v;
				else
					if(extreme[9]<v)
						extreme[9]=v;
			}
	dx=(extreme[7]-extreme[6])/639;
	dy=extreme[9]-extreme[8];
return;
}

void plotexpp(void)
{
int raza;
extern char statpexp[];
extern int npexp;
extern double pexpx[],pexpy[],pexpz[],extreme[],dx,dy;
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
	for(int i=0;i<npexp;i++)
	{
		if(statpexp[i])
		{
			setcolor(15);
			raza=2;
		}
		else
		{
			setcolor(9);
			raza=1;
		}
		circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
		((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,raza);
	}
	return;
}

void grafcond(void)
{
static float theta=90,phi=0;
extern int npgrx,npgry;
void recalcul(void);
void vertoriz(double,double);
	printf("No. of points in graphic along X axis (max. 63)= ");
	scanf("%d",&npgrx);
	if(npgrx<2)
	{
		npgrx=2;
		puts("We augmented at 2 !");
	}
	else
		if(npgrx>63)
		{
			npgrx=63;
			puts("We have diminuated at 63 !");
		}
	printf("No. of points in graphic along Y axis (n-1 -> max. 63) = ");
	scanf("%d",&npgry);
	if(npgry<2)
	{
		npgry=2;
		puts("We augmented at 2 !");
	}
	else
		if(npgry>63)
		{
			npgry=63;
			puts("We diminuated at 63 !");
		}
extern double oriz[],vert[];
int s;
	do
	{
		puts("Projection: Cavalier, Symmetric, Axonometric (c/s/a) ?");
		s=bioskey(0);
		switch(s)
		{
		case 11875:
			vert[0]=0;
			vert[1]=0.5;
			vert[2]=1;
			oriz[0]=1;
			oriz[1]=-0.5;
			oriz[2]=0;
			break;
		case 8051:
			oriz[0]=0.866;
			oriz[1]=-.866;
			oriz[2]=0;
			vert[0]=-.5;
			vert[1]=-.5;
			vert[2]=1;
			break;
		case 7777:
			printf("Angle on the horizontal (%f) = ",theta);
			scanf("%f",&theta);
			printf("Azimuth (%f) = ",phi);
			scanf("%f",&phi);
			vertoriz(theta,phi);
		default:
			break;
		}
	}
	while(s!=11875&&s!=8051&&s!=7777);
extern int linii;
	printf("Lines on graph :\n	1 only X\n	2 X and Y\n	3 only Y\n(1/2/3) ? ");
	scanf("%d",&linii);
	recalcul();
	return;
}

void pregra(double *pv)
{
extern int npgrx,npgry;
extern double xg[64],yg[64],zg[64][64],extreme[];
void recalcul(void);
double func(double xx,double xy,double *pv);
	double dx=(extreme[1]-extreme[0])/npgrx;
	double xx=extreme[0];
	for(int i=0;i<=npgrx;i++)
	{
		xg[i]=xx;
		xx+=dx;
	}
	dx=(extreme[3]-extreme[2])/npgry;
	xx=extreme[2];
	for(i=0;i<=npgry;i++)
	{
		yg[i]=xx;
		xx+=dx;
	}
	for(int j=0;j<=npgrx;j++)
		for(i=0;i<=npgry;i++)
		{
			xx=zg[j][i]=func(xg[j],yg[i],pv);
			if(extreme[4]>xx)
				extreme[4]=xx;
			else
				if(extreme[5]<xx)
					extreme[5]=xx;
		}
	recalcul();
	return;
}

void funcgra(void)
{
int j,i;
extern int npgrx,npgry,linii;
extern double xg[64],yg[64],zg[64][64];
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
	double dx=(extreme[7]-extreme[6])/639;
	double dy=extreme[9]-extreme[8];
	setcolor(4);
	if(linii<3)
		for(i=0;i<=npgry;i++)
		{
			moveto((horizont(xg[0],yg[i],zg[0][i])-extreme[6])/dx,
				((vertical(xg[0],yg[i],zg[0][i])-extreme[8])/dy-1)* -399);
			for(j=1;j<=npgrx;j++)
				lineto((horizont(xg[j],yg[i],zg[j][i])-extreme[6])/dx,
				((vertical(xg[j],yg[i],zg[j][i])-extreme[8])/dy-1)* -399);
		}
	setcolor(3);
	if(linii>1)
		for(i=0;i<=npgrx;i++)
		{
			moveto((horizont(xg[i],yg[0],zg[i][0])-extreme[6])/dx,
					((vertical(xg[i],yg[0],zg[i][0])-extreme[8])/dy-1)* -399);
			for(j=1;j<=npgry;j++)
				lineto((horizont(xg[i],yg[j],zg[i][j])-extreme[6])/dx,
					((vertical(xg[i],yg[j],zg[i][j])-extreme[8])/dy-1)* -399);
		}
	return;
}

void erori(double *pv)
{
double f;
extern int npexp;
extern char statpexp[];
extern double pexpx[],pexpy[],pexpz[],extreme[];
double func(double xx,double yy,double *pv);
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
double dx=(extreme[7]-extreme[6])/639;
double dy=extreme[8]-extreme[9];
	for(int i=0;i<npexp;i++)
	{
		if(statpexp[i])
			setcolor(14);
		else
			setcolor(9);
		f=func(pexpx[i],pexpy[i],pv);
		moveto((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
				((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy+1)*399);
		lineto((horizont(pexpx[i],pexpy[i],f)-extreme[6])/dx,
				((vertical(pexpx[i],pexpy[i],f)-extreme[8])/dy+1)*399);
		if(statpexp[i])
		{
			linerel(2,0);
			linerel(-4,0);
		}
	}
	return;
}

double vert[3],oriz[3];

double horizont(double x,double y,double z)
{
extern double oriz[];
	x*=oriz[0];
	x+=y*oriz[1];
	x+=z*oriz[2];
	return(x);
}

double vertical(double x,double y,double z)
{
extern double vert[];
	x*=vert[0];
	x+=vert[1]*y;
	x+=vert[2]*z;
	return(x);
}

void grafelim(void)
{
extern int npexp;
extern double pexpx[],pexpy[],pexpz[],extreme[],dx,dy;
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
void schimba(int a);
int creste(int a,int b);
int i=0,delta;
int ans=0;
	setcolor(12);
	circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
	((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,3);
	do
	{
		ans=bioskey(0);
		switch(ans)
		{
		case 18432:
			delta=10;
			break;
		case 20480:
			delta=-10;
			break;
		case 19712:
			delta=1;
			break;
		case 19200:
			delta=-1;
			break;
		case 7181:
			schimba(i);
		default:
			delta=0;
			break;
		}
		setcolor(0);
		circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
		((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,3);
		i=creste(i,delta);
		setcolor(12);
		circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
		((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,3);
	}
	while(ans!=283);
	setcolor(0);
	circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
	((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,3);
	return;
}

void schimba(int i)
{
int raza;
extern char statpexp[];
extern int npexp;
extern double pexpx[],pexpy[],pexpz[],extreme[],dx,dy;
double horizont(double x,double y,double z);
double vertical(double x,double y,double z);
	if(statpexp[i])
	{
		setcolor(9);
		raza=1;
		statpexp[i]=0;
	}
	else
	{
		setcolor(14);
		raza=2;
		statpexp[i]=1;
	}
	circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
	((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,raza);
	setcolor(0);
	circle((horizont(pexpx[i],pexpy[i],pexpz[i])-extreme[6])/dx,
	((vertical(pexpx[i],pexpy[i],pexpz[i])-extreme[8])/dy-1)* -399,3-raza);
}

int creste(int a,int b)
{
extern int npexp;
	a+=b;
	if(a<0)
		a+=npexp;
	else
		if(a>=npexp)
			a-=npexp;
	return(a);
}

void vertoriz(double theta,double phi)
{
extern double oriz[],vert[];
	oriz[0]=-sin(phi*M_PI/180);
	oriz[1]=cos(phi*M_PI/180);
	oriz[2]=0;
	vert[0]=-sin(theta*M_PI/180)*oriz[1];
	vert[1]=sin(theta*M_PI/180)*oriz[0];
	vert[2]=cos(theta*M_PI/180);
	return;
}