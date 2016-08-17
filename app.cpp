/*
	g++ declr.h
	g++ -c defn.cpp			
	g++ app.cpp defn.o
	./a.out
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "declr.h"
using namespace std;
	
	
int main()
{
	system("cls");	 
	list l;	int ch;	
	l.rftl();	
	while(1)
	{	
		cout<<"\n\n";		
		ch=menul();
		pt *tp; int ti; string ts;
			switch(ch)
			{
				case 1: l.addl();			 		 break;
				case 2: l.sid();  					 break;
				case 3: l.snm();					 break;
				case 4: l.dispall();				 break;
				case 5: l.modl();					 break;
				case 6: l.delp();			 	         break;
				case 7: tp=l.sid();	if(tp!=NULL) 	tp->addv();  	 break;				
				case 8: tp=l.sid(); 	if(tp!=NULL)	tp->sv();    	 break;
				case 9:tp=l.sid();	if(tp!=NULL)	tp->dispallv();	 break;				
				case 10:l.dispd();		break;
				case 11:l.wtof();	exit(0);  	
				default:cout<<"\nWrong Choice!!! ";
			}			
	}
	return 0;
}

