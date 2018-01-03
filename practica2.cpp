#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<cctype>

//C:\Users\T430\Documents\ejercicios programacion notepad++    
//g++ -o practica2.exe practica2.cpp
//practica2.exe 
using namespace std;
typedef enum { Rojo, Azul, Verde, Amarillo, Marron, Blanco, Incorrecto } tColor; //tipo enumerado de los posibles colores que puede usar el programa
const int tam =4;
typedef tColor tCodigo[tam];
int menu();
char color2char(tColor color);
void mostrarEleccion(tColor colorM,tCodigo codigoM, char letraM);
tColor char2color(string cadena, int i);
void codigoAletorio(tCodigo codigoM, bool admiteRepetido);
void compararCodigos(const tCodigo codigoM, const tCodigo hipotesis, int& colocados, int& descolocados);
void introducirHipotesis(tCodigo hipotesis);
void mostrarDescripcion();// funcion para mostrar la descripcion del juego

int main(){
	int intentos=1, longitud, colocados=0, descolocados=0;
	tColor colorM, colorH;
	tCodigo codigoM, hipotesis;
	srand(time(NULL));
	tCodigo codigo;
	char codigoH[tam];
	bool admiteRepetido, winner=false;
	char letraM, letraH;
	string cadena;
    mostrarDescripcion();
	int opcion=menu();
	while(opcion!=0){
		switch(opcion){
			case 1: {
				admiteRepetido=false;
				codigoAletorio(codigoM, admiteRepetido);
			    mostrarEleccion(colorM, codigoM ,letraM);
				while((intentos!=16)&&(winner==false)){
				 introducirHipotesis(hipotesis);
				 compararCodigos(codigoM, hipotesis, colocados, descolocados);
				  if (colocados==4){
					  winner=true;
				     cout<< " Enhorabuena! Lo encontraste!"<<endl;
				     cout<<" Te ha costado "<<intentos<<"intento(s)"<<endl;
				    }
					intentos++;
					colocados=0;
					descolocados=0;//reiniciar para que no se sumen 
				}
				if(intentos==16){
				 cout<<" Has perdido , no has conseguido adivinar el codigo secreto !"<<endl;
			    }
			}
			break;
			case 2: {
				admiteRepetido=true;
				codigoAletorio(codigoM, admiteRepetido);
				mostrarEleccion(colorM, codigoM ,letraM);
				while((intentos!=16)&&(winner==false)){
				 introducirHipotesis(hipotesis);
				 compararCodigos(codigoM, hipotesis, colocados, descolocados);
				  if (colocados==4){
					 winner=true;
				     cout<< " Enhorabuena! Lo encontraste!"<<endl;
				     cout<<" Te ha costado "<<intentos<<"intento(s)"<<endl;
				    }
					intentos++;
					colocados=0;
					descolocados=0;//reiniciar para que no se sumen 
				}
				if(intentos==16){
					cout<<" Has perdido , no has conseguido adivinar el codigo secreto !"<<endl;
				}
			}
			break;
		}
		if(intentos==16){
		 cout<<" Has perdido , no has conseguido adivinar el codigo secreto !"<<endl;
		}
		opcion=menu();
	}
	return 0;
}

int menu(){ // funcion del menu
	int op;
	op=-1;
	while((op<0)||(op>2)){
		cout << " 1. Jugar con un codigo sin colores repetidos "<<endl;
		cout << " 2. Jugar con un codigo con colores repetidos "<<endl;
		cout << " 0. Salir "<<endl;
		cout << "\n Elige una opcion : ";
		cin >> op;
		if((op<0)||(op>2)){
			cout << "\nOpcion incorrecta. Prueba otra vez : ";
			cin >> op;
		}
	}
	return op;
}
	
char color2char(tColor color){ // funcion que convierte un entero relacionado con el tipo enumerado en una letra correspondiente al color
	char caracter;
	if(color==Rojo){
		caracter='R';
	}
	if(color==Azul){
		caracter='Z';
	}
	if(color==Verde){
		caracter='V';
	}
	if(color==Amarillo){
		caracter='A';
	}
	if(color==Marron){
		caracter='M';
	}
	if(color==Blanco){
		caracter='B';
	}
	if(color==Incorrecto){
	 caracter='I';
	}
	return caracter;
}

tColor char2color(string cadena, int i){
 tColor color;
 cadena[i]=toupper(cadena[i]);//para que se pueda usar tanto minusculas como mayusculas

 switch(cadena[i]){
	 case 'R':{
		 color=Rojo;
		 break;
	    }
	 case 'Z': {
		 color=Azul; 
		 break;
	    }
	 case 'V': {
		 color=Verde; 
		 break;
		}
	 case 'A': {
		 color=Amarillo; 
		 break;
	    }
	 case 'M': {
		 color=Marron; 
		 break;
		}
	 case 'B': {
		 color=Blanco;
		 break;
		}
	 default: {
		 color=Incorrecto;
		}
	}
return color;
}

void mostrarDescripcion(){
	ifstream archivo;
	string cad;
	archivo.open("descripcion.txt");
    if(archivo.is_open()){
     getline(archivo,cad);
	 while(cad!="X"){
	     cout<<cad<<endl;
		 getline(archivo,cad);
	    }
    }
    else{ 
     cout<< " No se pudo abrir el archivo "<<endl;
    }
 }
  
void codigoAletorio(tCodigo codigoM, bool admiteRepetido){
	int eleccion;
	bool igual=false;
	if(admiteRepetido==true){
		for(int i=0;i<tam;i++){
		  eleccion=rand()%(6);
		  codigoM[i]=tColor(eleccion);
		}
	}
	else{
		for(int p=0;p<tam;p++){
		 eleccion=(rand()%(6));
		 codigoM[p]=tColor(eleccion);
		}
		for(int a=0;a<tam;a++){
			for(int b=0;b<tam;b++){
				if(a!=b){
					while(codigoM[a]==codigoM[b]){
						eleccion=rand()%(6);
						codigoM[b]=tColor(eleccion);
					}
				}
			}
		}
		for(int c=0;c<tam;c++){
			for(int d=0;d<tam;d++){
				if(c!=d){
					if(codigoM[c]==codigoM[d]){
						igual=true;
					}
				}
			}
		}
		while(igual==true){
		 for(int c=0;c<tam;c++){
			  for(int d=0;d<tam;d++){
				   if(c!=d){
				      while(codigoM[c]==codigoM[d]){
				          eleccion=rand()%(6);
					     codigoM[d]=tColor(eleccion);
					    }
				    }
			    }
		    }
		
	    }
    }
}

void introducirHipotesis(tCodigo hipotesis){
	string cadena;
	int longitud;
	cout<<" Introduce el codigo (palabra de 4 letras con alguna de R(1), Z(2), V(3), A(4), M(5) o B(6): "<<endl;
	cout<<" Codigo : ";
	cin>>cadena;
	longitud=cadena.length();
	while(longitud!=4){
		cout<<" Codigo incorrecto, vuelve a introducir un codigo. "<<endl;
		cout<<" Codigo : ";
		cin>>cadena;
		longitud=cadena.length();
	}
	for(int i=0;i<tam;i++){
	 hipotesis[i]=char2color(cadena, i);
	 while((hipotesis[i]==Incorrecto)||(longitud!=4)){
		 cout<<" Codigo incorrecto, vuelve a introducir un codigo. "<<endl;
		 cout<<" Codigo : ";
		 cin>>cadena;
		 longitud=cadena.length();
		 hipotesis[i]=char2color(cadena, i);
	    }
	}
}
	
void compararCodigos(const tCodigo codigoM, const tCodigo hipotesis, int& colocados, int& descolocados){
	typedef bool tComp[4];//VAMR
	tComp comparacionH;
	tComp comparacionM;
	for(int i=0;i<tam;i++){
		comparacionM[i]=false;
		comparacionH[i]=false;
	}
  	for(int z=0;z<tam;z++){//VAMR y RRRR
		if(codigoM[z]==hipotesis[z]){// VyR  AyR MyR RyR
			colocados++;
			comparacionM[z]=true;
		}
	}
	if(colocados!=tam){
       for(int j=0;j<tam;j++){
		  if(comparacionM[j]==false){
		     for(int e=0;e<tam;e++){
			     if((j!=e)&&(comparacionH[e]==false)&&(comparacionM[j]==false)){
				     if(codigoM[j]==hipotesis[e]){
					     descolocados++;
					     comparacionH[e]=true;
					     comparacionM[j]=true;
					    }
				    }
				}
			}
		}
	
	}		
    cout<<" Colocados: "<<colocados<<"; Descolocados: "<<descolocados<<endl; 
}

void mostrarEleccion(tColor colorM,tCodigo codigoM, char letraM){
	for(int i=0;i<tam;i++){ // mostrar la eleccion del ordenador para depurar
	 cout<<codigoM[i]+1;
	 colorM=tColor(codigoM[i]);
	 letraM=color2char(colorM);
	 cout<<" --> "<<letraM<<endl;
	}
}
