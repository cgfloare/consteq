#include <stdio.h>

void initial(int nv,double *pv,double *c)
/* n.var.  val.of_var.  val.of_cor.  fix.param.  */
{
int i,k;
extern char namesch[];
	puts("parameter and correction values :");
	for(k=0;k<nv;k++)
	{
		printf("%2d  ",k);
		for(i=0;i<10;i++)
			printf("%c",namesch[10*k+i]);
		printf(" = %g	valoare noua : ",pv[k]);
		scanf("%lf",&pv[k]);
		printf("correction : ");
		scanf("%lf",&c[k]);
	}
	return;
}

void searchpar(long *n)
{
int i;
extern char namesch[];
	printf("npoints = ");
	scanf("%ld",&n[0]);
	printf("nsteps = ");
	scanf("%ld",&n[1]);
	printf(" ");
	for(i=0;i<n[2]*10;i++)
		printf("%c",namesch[i]);
	puts("");
	return;
}

