#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef  __MATH_H
#include <math.h>
#endif

double funcval(double *pv)
{
int i;
double s,t;
extern int npexp;
extern double pexpx[],pexpy[],pexpz[];
extern char statpexp[];
double func(double s,double t,double *pv);
	s=0;
	for(i=0;i<npexp;i++)
		if(statpexp[i])
		{
			t=func(pexpx[i],pexpy[i],pv);
			t-=pexpz[i];
			t*=t;
			s+=t;
		}
	return(s);
}

void inspect(double *pv)
{
double xx,yy;
double func(double xx,double yy,double *pv);
	while(1)
	{
		printf("xx = ");
		scanf("%lf",&xx);
		printf("yy = ");
		scanf("%lf",&yy);
		if(xx==0)
			break;
		printf("%f\n",func(xx,yy,pv));
	}
	return;
}

double correlation(double *pv)
{
int i,n0;
double f1,f2,y1,y2,fy,f,y;
extern int npexp;
extern char statpexp[];
extern double pexpx[],pexpy[],pexpz[];
double func(double xx,double yy,double *pv);
	f1=f2=y1=y2=fy=n0=0;
	for(i=0;i<npexp;i++)
		if(statpexp[i])
		{
			f=func(pexpx[i],pexpy[i],pv);
			y=pexpz[i];
			n0++;
			y1+=y;
			f1+=f;
			fy+=f*y;
			y*=y;
			f*=f;
			y2+=y;
			f2+=f;
		}
	fy*=n0;
	f2*=n0;
	y2*=n0;
	fy-=f1*y1;
	f1*=f1;
	y1*=y1;
	f2-=f1;
	f2=sqrt(f2);
	y2-=y1;
	y2=sqrt(y2);
	fy/=f2;
	fy/=y2;
	return(fy);
}

