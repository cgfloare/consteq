CONSTEQ example of input parameters for data file 'ibu1.txt'

Name of the data file (with extension): ibu1.txt
No. of lines = 4
from which of the substance A (the first) = 3

(here you have made a mistake putting '40'! by 'lines' we have 
thought NMR lines, and not how many lines in the data file. 
The first 3 NMR lines are of the first substance, the last ones 
of the second substance. In 'ibu1.txt' second colum you see that
are 4 NMR lines investigated)

sum of concentrations A + B = 10
No. of points in graphic along X axis (maximum 63) = 63
No. of points in graphic along Y axis = 3
Projection: Cavalier, Symmetric, Axonometric (c/s/a) ? a
Angle on the horizontal (90.00000) = 20
Azimuth (0.00000) = 55
Lines on graph :
	1. only X
	2. X and Y
	3. only Y
(1/2/3) ? 2
Parameter and correction values: (you can put here other values to verify the stability of the fit)
0 1/K (u.c.) = 4.77835e-299 new value = 0.1  
correction = 0.001
1 d1 = -2.8603e+333 new value = 0.1
correction = 0.001
2 d2 = 2.73112e-310 new value = 0.1
correction = 0.001
3 d3 = -1.66742e-66 new value = 0.1
correction = 0.001
4 d4 = -4.37909e-47 new value = 0.1
correction = 0.001
npoints = 2000
nsetps = 1000

...

This is what you are searching for !

After the fit you can push the spacebar and
you will have a menu

Initialization	   search Parameters    Continue
Eliminate/insert   iNspect   		coRrelation
Graphics 	   graph quAlity        Stop
(i/p/c
e/n/r
g/a/s)

For Graph you must push 'g'

You must wait a little !

Did you want axes (y/n) ? y

The extremes X are : 0 10 ; Did you want to change them ? (y/n) n
The extremes Y are : 1 4 ; Did you want to change them ? (y/n) n
The extremes Z are : 0 0.267538 ; Did you want to change them ? (y/n) n
(you can try 'y' also)

Choose the origin of X between 0 10; X0 = 0
Choose the origin of Y between 1 4; Y0 = 1
Choose the origin of 2 between 0 0.267538; Z0 = 0

The X axis from 0 to 10 with the origin at 0; Divide (y/n) n
The X axis from 1 to 4 with the origin at 1; Divide (y/n) n
The X axis from 0 to 0.267538 with the origin at 0; Divide (y/n) n 
(you can try 'y' also)

Now you will have the surface graph with axes!

Pushing the spacebar two times, the menu will appear again!

Choosing 'r', you will have the correlation coefficient = 0.992571

Chosing 'a', will guide you back on the menu for choosing the graph type!

With 'n' you can inspect the surface giving an 'xx=' and 'yy=' values
(to go out from here you must put 'xx=0' and any value for 'yy=')

'p' will show you the final parametres. (The last column is the Error)

's' will STOP the program and print the Final Values

FINAL VALUES:

0   1/K(u.c.)	1.5525810e-01     -> which correspond to K = 6439 M^(-1)
1   dc1		1.3406885e-01
2   dc2		2.6753832e-01	
3   dc3		1.1029304e-01
4   dc4		1.5925664e-01