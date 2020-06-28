#include<iostream>
#include <Windows.h>
using namespace std;

//#define or ||

const int DIM = 7;
const int TURN = 50; 		//numero di turni massimi giocabili 

enum colors{red=12, blue=9, def=15};

void Color(colors color)
{                                                     
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

struct Coordinate
{
	int rig;
	int col;
};

void InizializzaCampo (int M[DIM][DIM]);
void Visualizza (int M[DIM][DIM]);
void Inserimento (int M[DIM][DIM], int indice, Coordinate& rigcol);
bool ContUnoEDue (int M[DIM][DIM]);
bool ControlloStupido (int M[DIM][DIM], Coordinate rigcol);
    bool CtrlSpace (int M[DIM][DIM], Coordinate rigcol);
    bool CtrlFuori (int M[DIM][DIM], Coordinate rigcol);

bool CtrlWin (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlVert1 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlOriz1 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlOriz2 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlOriz3 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlOriz4 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlAlzabandiera1 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlAlzabandiera2 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlAlzabandiera3 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlAlzabandiera4 (int M[DIM][DIM], Coordinate rigcol, int nmonetina);
	bool CtrlMoscio1(int M[DIM][DIM], Coordinate rigcol,  int nmonetina);
	bool CtrlMoscio2(int M[DIM][DIM], Coordinate rigcol,  int nmonetina);
	bool CtrlMoscio3(int M[DIM][DIM], Coordinate rigcol,  int nmonetina);
	bool CtrlMoscio4(int M[DIM][DIM], Coordinate rigcol,  int nmonetina);

char rigiocare;	

int vittorieG1 = 0;
int vittorieG2 = 0;


int main()
{
	bool haappenagiocato1, vittoria;
	int Campo[DIM][DIM];
	int ndacontrollare;
	Coordinate rigacolonna;

	do
	{
		system("cls");
		
		Color(def);

    	InizializzaCampo (Campo);

		do
		{
			for (int cont = 0; cont < TURN; cont++)
			{
				Inserimento(Campo, cont, rigacolonna);
	
	    		if (rigacolonna.rig != -1 && rigacolonna.col != -1)					//controlli per la vittoria/pareggio [INIZIO]
				{
					haappenagiocato1 = ContUnoEDue(Campo);
					if (haappenagiocato1 == true) ndacontrollare = 1;
					if (haappenagiocato1 == false) ndacontrollare = 2;
					vittoria = CtrlWin(Campo, rigacolonna, ndacontrollare);
	
					if (vittoria == true)
					{
						Visualizza(Campo);
						if (haappenagiocato1 == true) 
						{
							Color(red);
							cout << "\n\n Giocatore 1 WINS!";
							vittorieG1++;
							Color(def);
						}
						
						if (haappenagiocato1 == false)
						{
							Color(blue);
							cout << "\n\n Giocatore 2 WINS!";
							vittorieG2++;
							Color(def);
						}
						
						break;
					}
				}
				else
				{
					cout << "\n\n   E' UN PAREGGIO!\n";
					system("pause>nul");
					return 0;
				}																	//controlli per la vittoria/pareggio [FINE]
			}
		} while (vittoria == false);
	
		system("pause>nul");
		system("cls");
		cout<<"      FORZA 4!\n\n";	
		cout<<"Volete rigiocare? [s/n]\n";
		cin>>rigiocare;
	
	}while(rigiocare == 's');
	
	system("cls");
	cout<<"      FORZA 4!\n\n";	
	cout<<"    Arrivederci!\n";

	system("pause>nul");
	return 0;
}


//--------------------------------------------------------------------------------------------------------- INIZIALIAZZA CAMPO

void InizializzaCampo (int M[DIM][DIM])
{
	for(int i=0; i<DIM; i++)
	{
		for(int j=0; j<DIM; j++)
		{
			M[i][j]=0;												
		}
	}
}

//--------------------------------------------------------------------------------------------------------- VISUALIZZA

void Visualizza (int M[DIM][DIM])
{
	cout<<"      FORZA 4! \n\n";
	cout<<"  Vittorie G1 = "<<vittorieG1<<endl;
	cout<<"  Vittorie G2 = "<<vittorieG2<<endl;
	
	for(int i=0; i<DIM; i++)
	{
		cout<<"   ";
        for(int j=0; j<DIM; j++)
		{
            if(M[i][j]==0)			//se 0 vuol dire che è una casella ignuda
			{
				cout<<"_";
				cout<<" ";
			}
			
			if(M[i][j]==1)			//se 1 vuol dire che quella casella è stata occupata dal giocatore 1
			{
				Color(red);
				cout<<"0";
				Color(def);
				cout<<" ";
			}
			
			if(M[i][j]==2)			//se 2 vuol dire che quella casella è stata occupata dal giocatore 2
			{
				Color(blue);
				cout<<"0";
				Color(def);
				cout<<" ";
			}
		}
		cout<<endl;	
	}
	
	
	cout<<endl<<"   ";
    for(int i=0; i<DIM; i++)
	{
            cout<<i+1<<" ";			//numeri colonne
    }
}

//---------------------------------------------------------------------------------------- INSERIMENTO

void Inserimento(int M[DIM][DIM], int indice, Coordinate& rigcol)
{
    int o1o2;
    bool ctrl, inserisci2;
    
    inserisci2 = ContUnoEDue (M);
	
	if(inserisci2==true)  o1o2=2;
	if(inserisci2==false) o1o2=1;
	
	if(indice != TURN-1)
	{
		do
	   {
	            Visualizza (M);
				cout<<"\n\nGIOCATORE "<<o1o2<<endl;
				cout<<"Colonna di inserimento: "; 
		        cin>> rigcol.col;
				rigcol.col -=1;
	            ctrl = ControlloStupido (M, rigcol);
		            
	            if(ctrl==false) 
				{
					system("cls");
					cout<<"C'e' qualcosa che non va... reinserisci la colonna.\n\n";
				}
	            
	    } while(ctrl==false);
	    
		
	    for(int i=0; i<DIM; i++)
	    {
	    	if(M[i][rigcol.col]==1 or M[i][rigcol.col]==2)
	    	{
	    		M[i-1][rigcol.col] = o1o2;
				rigcol.rig = (i-=1);
	    		break;
			}
			if(i==DIM-1)
			{
				M[i][rigcol.col] = o1o2;
				rigcol.rig = i;
				system("cls");
			}
		}
		system("cls");
	}
	else
	{
		Visualizza (M);
		rigcol.rig = -1;
		rigcol.col = -1;
	}
}

//----------------------------------------------------------------------------------------  CONTROLLO UTENTE STUPIDO

bool ControlloStupido(int M[DIM][DIM], Coordinate rigcol)
{
	bool ctrl = true;
	bool colLibera= CtrlSpace(M, rigcol);
	bool colDentro= CtrlFuori(M, rigcol);
    
    if(colLibera == false) ctrl = false;
    if(colDentro == false) ctrl = false;
    return ctrl;
}

//----------------------------------------------------------------------------------------  controlla se c'è spazio in quella colonna

bool CtrlSpace(int M[DIM][DIM], Coordinate rigcol)
{
     bool ctrl=true;
     
     if(M[0][rigcol.col]==1 or M[0][rigcol.col]==2)
     {
          ctrl = false;           
     }
     
     return ctrl;
}

//----------------------------------------------------------------------------------------  controlla se l'inserimento è fuori dalle  colonne

bool CtrlFuori (int M[DIM][DIM], Coordinate rigcol)
{
	bool ctrl = true;
	
	if(rigcol.col<0 or rigcol.col>6) ctrl = false;
	return ctrl;
}

//---------------------------------------------------------------------------------------- conta gli 1 e i 2 in modo da capire quale sarà il prossimo numero che andrà inserito

bool ContUnoEDue (int M[DIM][DIM])
{
	bool ins2 = true; //inserisci 2
	int piu1=0, piu2=0;
	
	for(int i=0; i<DIM; i++)
	{
		for(int j=0; j<DIM; j++)
		{
				if(M[i][j]==1) piu1+=1;
				if(M[i][j]==2) piu2+=1;
		}
	}
	
	if(piu1==piu2)
	{
		ins2 = false;
	}
	return ins2;
}

//---------------------------------------------------------------------------------------- CONTROLLI VITTORIA

bool CtrlWin(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool vittoria = false;
	bool vert1 = false, vert2 = false, vert3 = false, vert4 = false;
	bool oriz1 = false, oriz2 = false,  oriz3 = false, oriz4 = false;
	bool alzabandiera1 = false,	alzabandiera2 = false, alzabandiera3 = false, alzabandiera4 = false;
	bool moscio1 = false, moscio2 = false, moscio3 = false, moscio4 = false;
	//---------------------------

	if (rigcol.rig <= 3)														//====> primo gruppo da 3
	{
		vert1 = CtrlVert1(M, rigcol, nmonetina);
		if (vert1 == true)
		{
				vittoria = true;
				return vittoria;
		}

		if (rigcol.col >= 3)
		{
			alzabandiera4 = CtrlAlzabandiera4(M, rigcol, nmonetina);
			if (alzabandiera4 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}

		if (rigcol.col <= 3)
		{
			moscio1 = CtrlMoscio1(M, rigcol, nmonetina);
			if (moscio1 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}
	}

	if (rigcol.rig >= 1 && rigcol.rig <= 4)										//====> secondo gruppo da 3
	{

		if (rigcol.col >= 2 && rigcol.col <= 5)
		{
			alzabandiera3 = CtrlAlzabandiera3(M, rigcol, nmonetina);
			if (alzabandiera3 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}

		if (rigcol.col >= 1 && rigcol.col <= 4)
		{
			moscio2 = CtrlMoscio2(M, rigcol, nmonetina);
			if (moscio2 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}
	}
	
	if (rigcol.rig >= 2 && rigcol.rig <= 5)										//====> terzo gruppo da 3
	{

		if (rigcol.col >= 1 && rigcol.col <= 4)
		{
			alzabandiera2 = CtrlAlzabandiera2(M, rigcol, nmonetina);
			if (alzabandiera2 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}

		if (rigcol.col >= 2 && rigcol.col <= 5)
		{
			moscio3 = CtrlMoscio3(M, rigcol, nmonetina);
			if (moscio3 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}
	}

	if ( rigcol.rig >= 3)														//====> quarto gruppo da 3
	{

		if (rigcol.col <= 3)
		{
			alzabandiera1 = CtrlAlzabandiera1(M, rigcol, nmonetina);
			if (alzabandiera1 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}

		if (rigcol.col >= 3)
		{
			moscio4 = CtrlMoscio4(M, rigcol, nmonetina);
			if (moscio4 == true)
			{
				vittoria = true;
				return vittoria;
			}
		}
	}
	
	if (rigcol.col <= 3)														//====> oriz 1
	{
		oriz1 = CtrlOriz1(M, rigcol, nmonetina);
		if (oriz1 == true)
		{
			vittoria = true;
			return vittoria;
		}
	}

	if (rigcol.col >= 1 && rigcol.col <= 4)										//====> oriz 2
	{
		oriz2 = CtrlOriz2(M, rigcol, nmonetina);
		if (oriz2 == true)
		{
			vittoria = true;
			return vittoria;
		}
	}

	if (rigcol.col >= 2 && rigcol.col <= 5)										//====> oriz 3
	{
		oriz3 = CtrlOriz3(M, rigcol, nmonetina);
		if (oriz3 == true)
		{
			vittoria = true;
			return vittoria;
		}
	}
		
	if (rigcol.col >= 3)														//====> oriz 4
	{
		oriz4= CtrlOriz4(M, rigcol, nmonetina);
		if (oriz4 == true)
		{
			vittoria = true;
			return vittoria;
		}
	}


	return vittoria;
}

//---------------------------------------------------------------------------------------- controllo vittoria verticale. insermento 1 dall'alto

bool CtrlVert1(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col] == nmonetina)
	{
		if (M[rigcol.rig + 2][rigcol.col] == nmonetina)
		{
			if (M[rigcol.rig + 3][rigcol.col] == nmonetina)
			{
				win = true;
			}
		}
	}
	
	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria verticale. insermento 2 dall'alto

bool CtrlVert2(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col] == nmonetina)
	{
		if (M[rigcol.rig + 2][rigcol.col] == nmonetina)
		{
			if (M[rigcol.rig - 1][rigcol.col] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria verticale. insermento 3 dall'alto

bool CtrlVert3(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col] == nmonetina)
	{
		if (M[rigcol.rig - 1][rigcol.col] == nmonetina)
		{
			if (M[rigcol.rig - 2][rigcol.col] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria verticale. insermento 4 dall'alto

bool CtrlVert4(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig - 1][rigcol.col] == nmonetina)
	{
		if (M[rigcol.rig - 2][rigcol.col] == nmonetina)
		{
			if (M[rigcol.rig - 3][rigcol.col] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria orizzontale. insermento 1 da sinistra

bool CtrlOriz1(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.col][rigcol.col +1] == nmonetina)
	{
		if (M[rigcol.rig][rigcol.col +2] == nmonetina)
		{
			if (M[rigcol.rig][rigcol.col +3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria orizzontale. insermento 2 da sinistra

bool CtrlOriz2(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.col][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig][rigcol.col + 2] == nmonetina)
		{
			if (M[rigcol.rig][rigcol.col - 1] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria orizzontale. insermento 3 da sinistra

bool CtrlOriz3(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.col][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig][rigcol.col - 1] == nmonetina)
		{
			if (M[rigcol.rig][rigcol.col - 2] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria orizzontale. insermento 4 da sinistra

bool CtrlOriz4(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig][rigcol.col -1] == nmonetina)
	{
		if (M[rigcol.rig][rigcol.col -2] == nmonetina)
		{
			if (M[rigcol.rig][rigcol.col -3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria alzabandiera. insermento 1 da sinistra

bool CtrlAlzabandiera1 (int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig - 1][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig - 2][rigcol.col + 2] == nmonetina)
		{
			if (M[rigcol.rig - 3][rigcol.col + 3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria alzabandiera. insermento 2 da sinistra

bool CtrlAlzabandiera2(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col - 1] == nmonetina)
	{
		if (M[rigcol.rig - 1][rigcol.col + 1] == nmonetina)
		{
			if (M[rigcol.rig - 2][rigcol.col + 2] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria alzabandiera. insermento 3 da sinistra

bool CtrlAlzabandiera3(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig - 1][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig + 1][rigcol.col - 1] == nmonetina)
		{
			if (M[rigcol.rig + 2][rigcol.col - 2] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria alzabandiera. insermento 4 da sinistra

bool CtrlAlzabandiera4(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col - 1] == nmonetina)
	{
		if (M[rigcol.rig + 2][rigcol.col - 2] == nmonetina)
		{
			if (M[rigcol.rig + 3][rigcol.col - 3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria moscio. insermento 1 da sinistra

bool CtrlMoscio1(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig + 2][rigcol.col + 2] == nmonetina)
		{
			if (M[rigcol.rig + 3][rigcol.col + 3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria moscio. insermento 2 da sinistra

bool CtrlMoscio2(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig + 2][rigcol.col + 2] == nmonetina)
		{
			if (M[rigcol.rig - 1][rigcol.col - 1] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria moscio. insermento 3 da sinistra

bool CtrlMoscio3(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig + 1][rigcol.col + 1] == nmonetina)
	{
		if (M[rigcol.rig - 1][rigcol.col - 1] == nmonetina)
		{
			if (M[rigcol.rig - 2][rigcol.col - 2] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}

//---------------------------------------------------------------------------------------- controllo vittoria moscio. insermento 4 da sinistra

bool CtrlMoscio4(int M[DIM][DIM], Coordinate rigcol, int nmonetina)
{
	bool win = false;

	if (M[rigcol.rig - 1][rigcol.col - 1] == nmonetina)
	{
		if (M[rigcol.rig - 2][rigcol.col - 2] == nmonetina)
		{
			if (M[rigcol.rig - 3][rigcol.col - 3] == nmonetina)
			{
				win = true;
			}
		}
	}

	return win;
}
