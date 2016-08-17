/*
prototypes of functions and classes
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cmath>

using namespace std;
	


	
	class pt;	// class for patient
	class list;	//list ka class
	class date;
	class vis;	
	pt* 		create();	// global function associated to list
	vis* 		pvis(); 	//fun for visit of p
	int 		mfy();    	// function asking whether to change contents or not	
	void		switchf(int);//*
	int			menul();
	class date
	{
		public:	int d,m,y; 
			date();	
   	};


	
	class vis //visit class
	{
		public:	
		int vn;	         	//visit no.
		char	nod[100];    	// name of disease
		char prs[50][100];     //*prescriptions		
		double	fee;        	// fees
		date dov;		// date of visit
		int w;			// weight
		int pov;		// size of vector prs
		void dispv(); 		// display visit
		~vis(){ }
		
	};

	
	class pt //patient class
	{
		public:	
		long long unsigned int 		pid;/* patient Id,name,disease,prescriptions,fees,date of enroll */
		char		pnm[100];			// patien name
		date		doe;			// date of enrollment
		vis	 	v[20];		//vector of visits( only recent 5 visits would be available)
		int		vor;			// size of vector v
		pt 		*nxt;	// pointer to next object
		void 		disp();	// function to disp object
		void 		mod();	// function to modify object data
		void		addv(); //add visit		
		void		dispallv();//disp all visits
		int		sv();//search visit		
		pt()
		{
			vor=0;
			nxt=NULL;			
		}
		~pt(){ }
	};


	class list //data struct implentn 
	{	
		public:
		pt *f;				// points to head of list
		int cnt;			//cnt of patients
		list(){ f=NULL; cnt=0;}	
		void addl();			/*add in list at beg; dispall; search_id;search_name; del_patient rec; mod_rec*/
		void dispall();			// display all
		pt* sid();			// search by ID
		pt* snm();			// search by name
		void delp();			// delete patient record
		void modl();			// modify patient record
		void dispd();			// display disease-vise
		void wtof();			// *write to file*
		void addrf( pt *p);		// * read from file*
		void rftl();
		~list(){ }
	};
	
/*	
	definations of functions 

*/
	
	time_t now = time(0);
	tm *lt = localtime(&now);

	date::date()
	{   y=1900 + lt->tm_year;
		m=1 + lt->tm_mon;
		d=lt->tm_mday;
	}

 
 //function to write data to file       
      void list::wtof()
	{	
		ofstream file;
	        pt tmp;        pt *t=f;		
		file.open("hosdata.dat",ios::binary | ios::out);		
		
	        while(t!=NULL)
		{
			tmp.pid=t->pid;
			strcpy(tmp.pnm,t->pnm);
			tmp.doe.d=t->doe.d;
			tmp.doe.m=t->doe.m;
			tmp.doe.y=t->doe.y;
			
			tmp.nxt=t->nxt;
			tmp.vor=t->vor;
			for(int i=0;i < t->vor; i++)
			{       				
				tmp.v[i].vn=t->v[i].vn;
				strcpy(tmp.v[i].nod,t->v[i].nod);
				tmp.v[i].fee=t->v[i].fee;
				tmp.v[i].pov=t->v[i].pov;
				for(int j=0;j < t-> v[i].pov ;j++)
				      strcpy(tmp.v[i].prs[j],t->v[i].prs[j]);				
				tmp.v[i].dov.d=t->v[i].dov.d;
				tmp.v[i].dov.m=t->v[i].dov.m;
				tmp.v[i].dov.y=t->v[i].dov.y;
				tmp.v[i].w=t->v[i].w;		
					
			}			
			file.write((char*)&tmp,sizeof(tmp));
			t=t->nxt;
			//tmp.disp();
		}

		file.close();
		cout<<"\nData Saved :)"; cout<<"\nTotal No of Records on Database:"<<cnt<<"\n";
	}



//fun end






//menu
	int menul()
	{	int ch; 
	cout<<"\n1.Add Patient Record\n2.Search Patient Record_ID\n3.Search Patient Record_Name\n4.Display Patient Record_ALL\n5.Modify Record_ID\n6.Delete Record_ID\n7.New Visit of Patient_ID\n8.Search Visit_VN\n9.Display Visits_ALL\n10.Display Patients Visits by Disease\n11.Exit";
		cout<<"\nEnter Choice:";		
		cin>>ch;
		return ch;
	}
//end of menu




//function to read from file
	
	void list::rftl()
	{
			
		ifstream rfile; pt tmp;
		
		rfile.open("hosdata.dat",ios::binary|ios::in);
		while(  rfile.read( (char*)&tmp,sizeof(tmp) )  )
		{	
				
			
			cnt++;
			pt *t=new pt;  			
        		t->pid=tmp.pid;	
			strcpy(t->pnm,tmp.pnm);
			t->doe.d=tmp.doe.d;	
			t->doe.m=tmp.doe.m;	
			t->doe.y=tmp.doe.y;	
			
			t->vor=tmp.vor;
			t->nxt=NULL;	
			        
			       for(int i=0; i< tmp.vor ;i++)
			        {  		        	
			       		t->v[i].vn=tmp.v[i].vn;
					strcpy(t->v[i].nod,tmp.v[i].nod);
					t->v[i].fee=tmp.v[i].fee;
					t->v[i].pov=tmp.v[i].pov;
					for(int j=0;j < t-> v[i].pov ;j++)
				        strcpy(t->v[i].prs[j],tmp.v[i].prs[j]);				
				 	t->v[i].dov.d=tmp.v[i].dov.d;
					t->v[i].dov.m=tmp.v[i].dov.m;
					t->v[i].dov.y=tmp.v[i].dov.y;
					t->v[i].w=tmp.v[i].w;		

        		
			        }
			
			addrf(t); 
			cout<<"\n"<<t->pid;
			  
		}
		rfile.close();
		cout<<"\nSystem Initialized :)";
		cout<<"\nTotal No of Records on Database:"<<cnt<<"\n";	
		
	}


	void list::addrf( pt *p)
	{	
		
		if(f==NULL)
		{
			f=p; return ;
		}
		p->nxt=f;
		f=p;
		return ;
	}



//function end


//function asking whether to change contents or not 
	int mfy()	
	{	char c; 
		cout<<"\tModify contents (Y/N)"; 
		cin>>c;	
		if(c=='y'||c=='Y')	
		return 1; 

		return 0;
	}
//function end


//fun for visit of p 

	vis  pvis(int vor)
	{ 	
		int i; char tmp[100];
		vis q;		
		vis *p=&q;
		p->vn=vor+1;
		cout<<"\nVisit No:"<<p->vn;
		cout<<"\nDate of Visit(DD/MM/YYYY):"<<p->dov.d<<"/"<<p->dov.m<<"/"<<p->dov.y;	
		z:cout<<"\nWeight:"; cin>>p->w; if(p->w<=0){ cout<<"\nInvalid Weight:"; goto z;}
		cout<<"\nDisease:"; cin.ignore(); cin.getline(p->nod,100); 		
		cout<<"\nPrescription(Enter '*' to end):\n";  
		//cin.ignore();
		i=0;
		do
		{	cout<<i+1<<":";
			cin.getline(tmp,100);
			if( ! strcmp(tmp,"*") ) break;
			strcpy(p->prs[i],tmp);	 
			i++;			
		}while(1);	
		p->pov=i;	
		cout<<"\nFee:"; cin>>p->fee;	
		return q;	

	}

	void pt::addv()//utility for list
	{	
		v[vor]=pvis(vor);
		vor++;		
	}
//function end


//function for disp of visit
	void    vis::dispv()
	{	
		cout<<"\n";
		cout<<"\n============================================================================================================";	
		cout<<"\nVisit No:"<<vn<<"\t\tDate of Visit(DD/MM/YYYY):"<<dov.d<<"/"<<dov.m<<"/"<<dov.y;		
		cout<<"\nDisease:"<<nod<<"\t\tWeight:"<<w<<"\t\tFee:"<<fee;;
		cout<<"\nPrescription:";  
		for(int i=0;i<pov;i++)
		cout<<"\n"<<i+1<<":"<<prs[i];		
		cout<<"\n============================================================================================================";	
		
	}


	void pt::dispallv()//utility for list
	{	
		cout<<"\n";	
		
		for(int i=0;i<vor;i++)
		{  cout<<"\n";v[i].dispv(); cout<<"\n";	}
	}
//function end




//function for search of visit
		int pt::sv()
		{					
			int tmp,i; 
			cout<<"Enter Visit No:"; cin>>tmp;
			for(i=0;i<vor;i++)
			{
				if(tmp==v[i].vn)
				{
					cout<<"\nRecord Found :)";
					disp();
					v[i].dispv();
					return 1;				
				}
			}
			if(i==vor)
			cout<<"\nNo Record Found!!! :(";
			return -1;
		}
//function end


// creating new object
	pt* create(int cnt) 
	{
		time_t nowt = time(0);
		tm *ltm = localtime(&nowt);
		pt *p=new pt; char tmp[100]; int i=0;
        	p->pid=(p->doe.y*pow(10,10)+p->doe.m*pow(10,8)+p->doe.d*pow(10,6)+(1 + ltm->tm_hour)*pow(10,4)+(1 + ltm->tm_min)*pow(10,2)+(1 + ltm->tm_sec));
		cout<<"\nDate of Enrollment(DD/MM/YYYY):"<<p->doe.d<<"/"<<p->doe.m<<"/"<<p->doe.y;
		cout<<"\nUIN:"<<p->pid;
		cin.ignore();
		cout<<"\nName:"; cin.getline(p->pnm,100); 
		p->addv();
		p->nxt=NULL;
	
		return p;
	}
//function end


// displaying object data member of pt
void pt::disp() 
	{	
		cout<<"\n";
		cout<<"\nUIN:"<<pid;
		cout<<"\tName:"<<pnm; 		
		cout<<"\nDate of Enrollment(DD/MM/YYYY):"; 
		cout<<doe.d<<"/"<<doe.m<<"/"<<doe.y;
	}
//function end


//modifying obj data mem of pt
	void pt::mod() 
	{
		char tmp[100]; int i;
		cout<<"\nUIN:"<<pid;
		cout<<"\nDate of Enrollment(DD/MM/YYYY):"<<doe.d<<"/"<<doe.m<<"/"<<doe.y;	
		cout<<"\nName:";   
		if(mfy())
		{ 	cout<<"\nName:";
			cin.ignore();
			cin.getline(pnm,100);
		}  
	}
//function end


//add in list
	void list::addl()
	{	
		cnt++;
		pt *tmp=create(cnt);
		if(f==NULL)
		{
			f=tmp; return ;
		}
		tmp->nxt=f;
		f=tmp;
		return ;
	}
	
	
//function end


//disp _ all objs
	void list::dispall() 
	{	
		pt *tmp=f;
		if(f==NULL)
		{
			cout<<"\nNo Records :( Abort !!!"; return ;
		}
		while(tmp!=NULL)
		{
			tmp->disp();
			tmp=tmp->nxt;
		}
		
	}
//function end


// mod obj

	void list::modl()
	{
		pt *tmp=sid();
		if(tmp!=NULL)		
		tmp->mod();
	}
//function end
	

// search by name
	pt* list::snm()
	{
		pt *tmp=f; char t[100];
		cout<<"\nEnter Patient Name:"; cin.ignore(); cin.getline(t,100);
		if(f==NULL)
		{
			cout<<"\nNo Records :( Abort !!!"; return NULL ;
		}
		while(tmp!=NULL)
		{
			if(t==tmp->pnm)
			{	cout<<"\n Record Found    :)  ";
				tmp->disp();
				return tmp;			
			}
			tmp=tmp->nxt;
		}
		cout<<"\nNo Record Found :( Abort !!!"; return NULL;

	}

//function end

	
//search by name
	pt* list::sid()
	{
		long long unsigned int t; pt *tmp=f;
		cout<<"\nEnter UIN:"; cin>>t;
		if(f==NULL)
		{
			cout<<"\nNo Records :( Abort !!!"; return NULL ;
		}
		while(tmp!=NULL)
		{
			if(t==tmp->pid)
			{	
				cout<<"\n Record Found    :)  ";
				tmp->disp();
				return tmp;					
			}
			tmp=tmp->nxt;
		}
		 cout<<"\nNo Record Found :( Abort !!!"; return NULL;
	}
//function end
	

//function to display visits by disease
		void list::dispd()
		{
			pt *tmp; char t[100]; int cd=0;
			tmp=f;
			cout<<"\nEnter Name of Disease:";
			cin.ignore();
			cin.getline(t,100);
			if(f==NULL)
			{
				cout<<"\nNo Records :( Abort !!!"; return  ;
			}
				while(tmp!=NULL)
				{
					for(int i=0;i < tmp->vor;i++)
					{
						if(!strcmp(t,tmp->v[i].nod) )
						{	
							cd++;
							tmp->disp(); 
							while(	i < tmp->vor)
							{
								if(!strcmp(t,tmp->v[i].nod) )
								tmp->v[i].dispv();
								i++;
							}
						}
					
					}
					tmp=tmp->nxt;
				}
					if(!cd) cout<<"\nNo Patients found for"<<t<<"disease.";
					else	cout<<"\nTotal Patients:"<<cd;
		}

//function end

//delete obj from list
	void list::delp()
	{	long long unsigned int t; pt *tmp,*tmp1; tmp=f; char c;
		cout<<"\nEnter UIN:"; cin>>t;
		if(f==NULL||(f->nxt==NULL&&f->pid!=t))
		{
			cout<<"\nNo Record :( Abort !!!"; return ;
		}		
		if(t==tmp->pid)
		{
			cout<<"\nPatient Name:"<<tmp->pnm;
			cout<<"\nDelete (Y/N)"; cin>>c;
			if(c=='y'||c=='Y')			
			{ f=tmp->nxt; delete tmp; cnt--; return ; }
			else 
			return ;

		}
		while(tmp!=NULL)
		{
			if(t==tmp->nxt->pid)
			{
				cout<<"\nPatient Name:"<<tmp->pnm;
				cout<<"\nDelete Sure ? (Y/N)"; cin>>c;
				if(c=='y'||c=='Y')
				{
					tmp1=tmp->nxt->nxt;								
					delete tmp->nxt;
					tmp->nxt=tmp1;
					cnt--;							
					return ;			
				}
				else 
				return ;
			}
			tmp=tmp->nxt;
		}
		 cout<<"\nNo Record Found :( Abort !!!";				

	}	
//function end

