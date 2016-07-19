#include <graphics.h>
#include <stdio.h>
#include <bios.h>

void preoptim(int nv)
{
int answ,k,i,s,gdrive=VGA,gmode=2;
long n[3];
double c[16],pv[16];
extern int npexp;
extern double pexpx[],pexpy[],pexpz[];
extern char namesch[],statpexp[];
int grafcond(void);
void grafica(int, double *pv);
void inspect(double *pv);
int search(long nsteps,long npoints,int nv,double *pv,double *c);
int search1(long nsteps,long npoints,double *a,double *c);
void searchpar(long *n);
void eliminate(void);
void initial(int nv,double *pv,double *c);
void initial1(int nv,double *pv,double *c);
int npgr;
double correlation(double *pv);
	for(i=0;i<npexp;i++)
		statpexp[i]=1;
	npgr=grafcond();
	initgraph(&gdrive,&gmode,"");
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
						puts("This is what you are searching for!");
					break;
					case 2:
						puts("Continue ! Modify parameters with <p> if you want.");
					break;
					case 0:
						if(nv==1)
						{
							puts("Raise npoints from <p> !");
							break;
						}
					default:
						puts("Something is bad !");
						return;
				}
				break;
			case 12654:
				inspect(pv);
				break;
			case 561:
				initial1(nv,pv,c);
				break;
			case 4978:
				printf("correlation coefficient = %f\n",correlation(pv));
				break;
			case 7777:
				npgr=grafcond();
			case 8807:
				puts("YOU MUST WAIT A LITTLE !");
				grafica(npgr,pv);
				break;
			case 4709:
				eliminate();
				break;
			default:
				puts("	Initialization        search Parameters      Continue");
				puts("	Eliminate/insert      iNspect                coRrelation");
				puts("	Graphics              graph quAlity          Stop");
				printf("	(i/p/c\n	 e/n/r\n	 g/a/s)\n ");
		}
		flushall();
		answ=bioskey(0);
	}
	while(answ!=8051);
	closegraph();
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

void eliminate(void)
{
extern char statpexp[];
extern int npexp;
int i;
char request='c';
void sector(int i);
	while(1)
	{
		switch(request)
		{
		case 'e':
			printf("point eliminated ");
			scanf("%d",&i);
			if(i<0||i>=npexp)
				sector(0);
			else
				statpexp[i]=0;
			request='c';
			break;
		case 'i':
			printf("point inserted ");
			scanf("%d",&i);
			if(i<0||i>=npexp)
				sector(1);
			else
			statpexp[i]=1;
			request='c';
			break;
		case 's':
			return;
		default:
			printf("Eliminate, Insert or Stop ");
			scanf("%s",&request);
			break;
		}
	}
}

void sector(int i)
{
extern int npexp;
extern char statpexp[];
int k1,k2,step;
	printf("from ");
	scanf("%d",&k1);
	if(k1<0)
		return;
	printf("to ");
	scanf("%d",&k2);
	if(k2>=npexp)
		return;
	printf("with step ");
	scanf("%d",&step);
	if(step<1||step>(k2-k1))
		return;
	for(int j=k1;j<=k2;j+=step)
		statpexp[j]=i;
	return;
}