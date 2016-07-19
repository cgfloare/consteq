#include <stdio.h>
#include <math.h>
#include <conio.h>
int npexp, nrlinii, nrliniia;
char statpexp[200];

char namesch[]={"1/K(u.c.) ëc1       ëc2       ëc3       ëc4       ëc5       ëc6       ëc7       ëc8       ëc9       ëc10      ëc11      ëc12      ëc13      ëc14      ëc15      "};

double sumaconc;
double pexpx[200], pexpy[200], pexpz[200];

void preoptim(int n_variabile);

void decread(int nmax)
{
FILE *filepoint;
char filenam[80];
extern int npexp;
extern double pexpx[],pexpy[],pexpz[];
	clrscr();
	printf("\t  CCC   OOO   N   N   SSS  TTTTT  EEEEE   QQQ\n");
	printf("\tC      O   O  NN  N  S       T    E      Q   Q\n");
	printf("\tC      O   O  N N N   SS     T    EEEE   Q   Q\n");
	printf("\tC      O   O  N  NN     S    T    E      Q   Q\n");
	printf("\t  CCC   OOO   N   N  SSS     T    EEEEE   QQQ\n");
	printf("\t                                             QQ\n\n");
	printf("\tCopyright INCDTIM, Cluj-Napoca, Romania.\n");
	printf("\tF. Baliban 1997 - Revised by C. Floare 2000\n");
	printf("\n\nName of the data file (with extension) : ");
	flushall();
	gets(filenam);
	if((filepoint=fopen(filenam,"r"))!=NULL)
	{
		npexp=0;
		while(!feof(filepoint))
		{
			fscanf(filepoint,"%lf %lf %lf",&pexpx[npexp],&pexpy[npexp],&pexpz[npexp]);
			npexp++;
			if(npexp==nmax)
			{
				printf("Data file too long !\nI have kept the first %d points\n",nmax);
				break;
			}
		}
		npexp--;
	}
	else
		puts("This is not a file !");
	fclose(filepoint);
	return;
}


double func(double x,double y,double *par)
{
int j=floor(y+0.1);
	if(par[0]<0)
		par[0]=-par[0];
double a=x;
double b=sumaconc-x;
double sum=a+b+par[0];
double discr=sum*sum-a*b*4;
	discr=sqrt(discr);
	sum-=discr;
	sum*=par[j];
	if(j<=nrliniia)
	{
		if(a==0)
			return(par[j]);
		sum/=a*2.0;
	}
	else
	{
		if(b==0)
			return(par[j]);
		sum/=b*2.0;
	}
	return(sum);
}

void main(void)
{
	decread(200);
	printf("No. of lines (n) = ");
	scanf("%d",&nrlinii);
	printf("from which of the substance A (the first) = ");
	scanf("%d",&nrliniia);
	printf("sum of concentrations A + B = ");
	scanf("%lf",&sumaconc);
	preoptim(nrlinii+1);
}