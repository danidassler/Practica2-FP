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
typedef int tCodigo[tam];
int menu();
char color2char(tColor color);
int char2color(string cadena);
void codigoAletorio(tCodigo codigoM, bool admiteRepetido);
void compararCodigos(const tCodigo codigoM, const tCodigo hipotesis, int& colocados, int& descolocados);
void introducirHipotesis();
void mostrarDescripcion();// funcion para mostrar la descripcion del juego

int main(){
	tColor color1;
	int intentos=1;
	int longitud;
	int colocados=0, descolocados=0;
	tColor colorM, colorH;
	tCodigo codigoM, hipotesis;
	srand(time(NULL));
	tCodigo codigo;
	char codigoH[tam];
	bool admiteRepetido;
	char letraM, letraH, letra1;
	int op, num;
	string cadena;
	cout<<"numero del color que elijes:";//prueba para ver si convierte el color en una letra
	cin>>op;
	color1=tColor(op-1);
	letra1=color2char(color1);
	cout<<letra1<<endl;
	// prueba prueba prueba prueba prueba prueba prueba (a partir de aqui bien)
    mostrarDescripcion();
	int opcion=menu();
	while(opcion!=0){
			switch(opcion){
				case 1: {
					admiteRepetido=false;
					codigoAletorio(codigoM, admiteRepetido);
					for(int i=0;i<tam;i++){ // mostrar la eleccion del ordenador para depurar
					 cout<<codigoM[i]+1;
					 colorM=tColor(codigoM[i]);
					 letraM=color2char(colorM);
					 cout<<" --> "<<letraM<<endl;	
					}
					while(intentos<3){
					 introducirHipotesis();
						intentos++;//mirar tener cuidado
					}
					
				}
				break;
				case 2: {
					admiteRepetido=true;
					codigoAletorio(codigoM, admiteRepetido);
					for(int i=0;i<tam;i++){ // mostrar la eleccion del ordenador para depurar
					 cout<<codigoM[i]+1;
					 colorM=tColor(codigoM[i]);
					 letraM=color2char(colorM);
					 cout<<" --> "<<letraM<<endl;	
					}
					while(intentos<15){
						
						}//pene
						intentos++;//mirar tener cuidado
					}
					
				}
				break;
			}
		
		 if(intentos==15){
			cout<< " Has agotado tus intentos "<<endl;
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
int char2color(string cadena){
	tColor color;
	
	for(int k=0;k<tam;k++){
		cadena[k]=toupper(cadena[k]);//para que se pueda usar tanto minusculas como mayusculas
	
	 switch(cadena[k]){
			  case 'R':{
			 color=Rojo;
			}
			break;
		 case 'Z': {
			 color=Azul; 
			}
			break;
		 case 'V': {
			 color=Verde; 
			}
			break;
		 case 'A': {
			 color=Amarillo; 
			}
			break;
		 case 'M': {
			 color=Marron; 
			}
			break;
		 case 'B': {
			 color=Blanco;
			}
			break;
		 default: {
			 color=Incorrecto;
		    }
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
		  codigoM[i]=eleccion;
		}
	}
	else{
		for(int p=0;p<tam;p++){
		 eleccion=(rand()%(6));
		 codigoM[p]=eleccion;
		}
		for(int a=0;a<tam;a++){
			for(int b=0;b<tam;b++){
				if(a!=b){
					while(codigoM[a]==codigoM[b]){
						eleccion=rand()%(6);
						codigoM[b]= eleccion;
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
					     codigoM[d]= eleccion;
					    }
				    }
			    }
		    }
		
	    }
    }
}

void introducirHipotesis(){
	string cadena;
	tCodigo hipotesis;
	int longitud;
	cout<<" Introduce el codigo (palabra de 4 letras con alguna de R(1), Z(2), V(3), A(4), M(5) o B(6): "<<endl;
	cout<<" Codigo : ";
	cin>>cadena;
	for(int i=0;i<tam;i++){
	 hipotesis[i]=char2color(cadena);
	}
	longitud=cadena.length();
	while(longitud!=4){
		cout<<" Codigo incorrecto, vuelve a introducir un codigo. "<<endl;
		cout<<" Codigo : ";
		cin>>cadena;
		for(int i=0;i<tam;i++){
		 hipotesis[i]=char2color(cadena);
		}
	}
}
	
void compararCodigos(const tCodigo codigoM, const tCodigo hipotesis, int& colocados, int& descolocados){
    for(int z=0;z<tam;z++){
		if(codigoM[z]==hipotesis[z]){
			colocados++;
		}
	}
	if(colocados==4){
		
		
	
	
	
	
	
	
	
}
	