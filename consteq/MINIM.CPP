#include <stdio.h>
#include <bios.h>
#include <stdlib.h>
#include <math.h>
              
void place(int nv,double *pv,double f)
{
int k;
	for(k=0;k<nv;k++)
		printf("%10.3e",pv[k]);
	printf("%15.7e\n",f);
	return;
}

int search(long nsteps,long npoints,int nv,double *pv,double *c)
{
long i,j;
int k,count,d[16];
double f1,f2,lsup=0.75,linf=0.25,v[16],w[16],x[16],y[16];
double funcval(double *pv);
	if(nv>16)
	{
		puts("TO MANY PARAMETERS FOR THE int search(...) FUNCTION !");
		return(0);
	}
	for(k=0;k<nv;k++)
	{
		x[k]=pv[k];
		d[k]=-1;
	}
	f1=funcval(pv);
	count=0;
	for(i=0;i<nsteps;i++)
	{
		count++;
		for(j=0;j<npoints;j++)
		{
			for(k=0;k<nv;k++)
			{
				f2=rand()/16384.+d[k];
				x[k]=f2*c[k]+pv[k];
				v[k]=f2;
			}
			f2=funcval(x);
			if(bioskey(1)==283)
			{
				bioskey(0);
				return(2);
			}
			if(f2<f1)
			{
				for(k=0;k<nv;k++)
				{
					y[k]=x[k];
					w[k]=v[k];
				}
				f1=f2;
				count=0;
			}
		}
		if(count==0)
			for(k=0;k<nv;k++)
			{
				pv[k]=y[k];
				f2=w[k];
				if(f2>lsup)
				{
					d[k]++;
					if(d[k]>0)
						d[k]=0;
					c[k]*=2;
				}
				if(f2<-lsup)
				{
					d[k]--;
					if(d[k]<-2)
						d[k]=-2;
					c[k]*=2;
				}
				if(fabs(f2)<linf)
				{
					c[k]/=2;
					d[k]=-1;
				}
			}
		else
			for(k=0;k<nv;k++)
			{
				c[k]/=2;
				d[k]=-1;
			}
		if(bioskey(1))
			bioskey(0);
		if(count)      //
			printf("* ");//
		place(nv,pv,f1);
		if(count>8)
			return(1);
	}
	return(2);
}

int search1(long nsteps,long npoints,double *a,double *c)
{
const double k=(sqrt(5)+1)/2;
long i;
double d,a0,a1,a2,b,f0,f1,f2,fb;
extern char namesch[];
void place(int nv,double *pv,double f);
double funcval(double *pv);
	a0=a[0];
	d=c[0];
	f0=funcval(&a0);
	a1=a0+d;
	f1=funcval(&a1);
	if(f1>f0)
	{
		b=a1;
		a1=a0;
		a0=b;
		fb=f1;
		f1=f0;
		f0=fb;
		d=-d;
	}
	i=0;
	while(1)
	{
		a2=d*k+a1;
		f2=funcval(&a2);
		place(1,&a2,f2);
		if(f2>f1)
			break;
		else
		{
			i++;
			if(i>npoints)
				return(0);
			a0=a1;
			f0=f1;
			a1=a2;
			f1=f2;
			d*=k;
		}
	}
	puts("");
	i=0;
	while(1)
	{
		b=d/k+a1;
		fb=funcval(&b);
		if(fb<f1)
		{
			a0=a1;
			f0=f1;
			a1=b;
			f1=fb;
		}
		else
		{
			a2=a0;
			f2=f0;
			a0=b;
			f0=fb;
			d=-d;
		}
		d/=k;
		place(1,&a1,f1);
		if(a1==a0)
			break;
		i++;
		if(i>nsteps)
		{
			a[0]=a0;
			c[0]=d;
			return(2);
		}
	}
	a[0]=a0;
	c[0]=d;
	printf("Minimum value %g for ",f0);
	for(i=0;i<10;i++)
		printf("%c",namesch[i]);
	printf(" = %g\n",a0);
	return(1);
}

void preopt1(int nv)
{
int answ,k,i,s;
long n[3];
int search(long nsteps,long npoints,int nv,double *pv,double *c);
int search1(long nsteps,long npoints,double *a,double *c);
void initial(int nv,double *pv,double *c);
void searchpar(long *n);
void initial1(int nv,double *pv,double *c);
double c[16],pv[16];
extern char namesch[];
	answ=5993;
	do
	{
		switch(answ)
		{
			case 5993:
				initial(nv,pv,c);
			case 6512:
				n[2]=long(nv);
				searchpar(n);
			case 11875:
				if(nv==1)
					s=search1(n[1],n[0],pv,c);
				else
					s=search(n[1],n[0],nv,pv,c);
				switch(s)
				{
					case 1:
						puts("Asta ai cautat !");
					break;
					case 2:
						puts("Continue ! Change the parameters with <p> if you want.");
					break;
					case 0:
						if(nv==1)
						{
							puts("Increase npoints from <p> !");
							break;
						}
					default:
						puts("Something is not good !");
						return;
				}
				break;
			case 561:
				initial1(nv,pv,c);
				break;
			default:
				puts("	Initialization		 Search Parameters		Continue");				puts("	Stop");
				printf("	(i/p/c\n	 s) ");
		}
		flushall();
		answ=bioskey(0);
	}
	while(answ!=8051);
	puts("FINAL VALUES :");
	for(k=0;k<nv;k++)
	{
		printf("%2d  ",k);
		for(i=0;i<10;i++)
			printf("%c",namesch[10*k+i]);
		printf("		%12.7e\n",pv[k]);
	}
	return;
}

void initial1(int nv,double *pv,double *c)
{
int i,k;
extern char namesch[];
	puts("Parameters values :");
	for(k=0;k<nv;k++)
	{
		printf("%2d  ",k);
		for(i=0;i<10;i++)
			printf("%c",namesch[10*k+i]);
		printf(" = % 11e",pv[k]);
		printf("		%2d cor = %8.2e\n",k+nv,c[k]);
	}
	while(1)
	{
		printf("Parameter no. ? ");
		scanf("%d",&k);
		if(k<0||k>=nv*2)
			break;
		if(k<nv)
		{
			for(i=0;i<10;i++)
				printf("%c",namesch[10*k+i]);
			printf(" = %8g	cor = %8g	",pv[k],c[k]);
			scanf("%lf %lf",&pv[k],&c[k]);
		}
		else
		{
			k-=nv;
			printf("correction %2d = %6e  new value ",k,c[k]);
			scanf("%lf",&c[k]);
		}
	}
	return;
}
