/* Simonas Paulikas, VGTU ELF Ef-15/2
   2D transformations implementation in C++ (Interface in LT)
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

using namespace std;

const int MaxP = 4;
const int buff_len=15;
const double PI = 3.141592;

struct trans{
		int order[5];
		int count;
		bool useP;
        float point[2];
        bool Tx_istrue, Ty_istrue;
        float T[2];
        bool Sx_istrue, Sy_istrue;
        float S[2];
        bool R_istrue;
        float R;
        bool Mx_istrue, My_istrue;
        float M[2];
        bool Lx_istrue, Ly_istrue;
        float L[2];
} t;

void read(float p[][3], int &npoints, trans &t);
void multiply(float a[][3], float b[][3], int row);
void transpose(trans t, float p[][3], int n);
void scale(trans t, float p[][3], int n);
void rotat(trans t, float p[][3], int n);
void mirror(trans t, float p[][3], int n);
void shear(trans t, float p[][3], int n);
void calc(float p[][3], int npoints, trans t);
void getcorn(float p[][3], int npoints, trans t);
void write(float p[][3], int n);

int main(){

    float p[MaxP][3]={0};
    int npoints;

    read(p, npoints, t);
	if(npoints == -1) return 0;

	calc(p, npoints, t);
	write(p, npoints);
	system("PAUSE");
	return 0;
}

void read(float p[][3], int &npoints, trans &t){
	
	char buff[buff_len];
	char * pch;
	t.count=0;
	cout << "\t2D transformaciju skaiciavimo programa\n\n";	
                                         
	cout << "Poslinkis - 1\nMastelis - 2\nPasukimas - 3\nAtspindys - 4\nSlytis - 5\n";
	cout << "Iveskite eiliskuma atskirdami skaicius kableliu, pvz 4, 2\n\t";
	fgets(buff, (buff_len), stdin);
	pch = strtok(buff, ". ,");
	while(pch != NULL){
		t.order[t.count] = atoi(pch);
		t.count++;
		pch = strtok(NULL, ". ,");
	}
	
	cout << "Iveskite duomenis, arba jei duomens neturite - palikite tuscia ir spauskite ENTER klavisa\n";

	for(int i=0; i<t.count; i++){
		switch(t.order[i]){
			case 1:{
				cout << "\nPoslinkis Tx = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Tx_istrue = false;
				else { t.T[0] = atof(buff); t.Tx_istrue = true; }	
				cout << "Poslinkis Ty = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Ty_istrue = false;
				else { t.T[1] = atof(buff); t.Ty_istrue = true; }
				break;
			}
			case 2:{
				cout << "\nMastelis Sx = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Sx_istrue = false;
				else { t.S[0] = atof(buff); t.Sx_istrue = true; }
				cout << "Mastelis Sy = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Sy_istrue = false;
				else { t.S[1] = atof(buff); t.Sy_istrue = true; }
				break;
			}
			case 3:{
				cout << "\nPosukio kampas Tetha = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.R_istrue = false;
				else { t.R = atof(buff); t.R_istrue = true; }
				break;
			}
			case 4:{
				cout << "\nKad atspindzio asis butu x=y, iveskite Mx= 1 ir My= 1";
				cout << "\nKad atspindys butu koordinaciu asiu pradzios tasko atzvilgiu, iveskite Mx= 0 ir My= 0";
				cout << "\nVisais kitais atvejais iveskite duotas reiksmes\n";
				cout << "\nAtspindzio asimi Mx = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Mx_istrue = false;
				else { t.M[0] = atof(buff); t.Mx_istrue = true; }
				cout << "Atspindzio asimi My = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.My_istrue = false;
				else { t.M[1] = atof(buff); t.My_istrue = true; }
				break;
			}
			case 5:{
				cout << "\nSlytis Lx = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Lx_istrue = false;
				else { t.L[0] = atof(buff); t.Lx_istrue = true; }
				cout << "Slytis Ly = ";
				fgets(buff, buff_len, stdin);
				if(buff[0] == '\n') t.Ly_istrue = false;
				else { t.L[1] = atof(buff); t.Ly_istrue = true; }
				break;
			}
			default: break;
		}
	}
	cout << "\nTaskas, apie kuri vykdomos transformacijos. Koordinate atskirkite tarpu. P = ";
	fgets(buff, (buff_len), stdin);
	if(buff[0] == '\n') t.useP = false;
	else{ 
		t.point[0] = atof(strtok(buff, " "));
		t.point[1] = atof(strtok(NULL, " "));
		t.useP = true;
	}
  
	cout << "Kiek objekto tasku ivesite? (max "<<MaxP<<"): ";
	cin >> npoints;
	if(npoints <= 0 || npoints > MaxP){ npoints = -1; return; }
	for(int i=0; i<npoints; i++){
		cout << "\n" << i+1 <<" taskas. x y: ";
		cin >> p[i][0] >> p[i][1];
		p[i][2] = 1;
	}
}

void multiply(float a[][3], float b[][3], int row){
	
	float c[MaxP][3]={0};
	for(int i=0; i<row; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}	
	}
	for(int i=0; i<row; i++){
		for(int j=0; j<3; j++){
			a[i][j] = c[i][j];
		}
	}
}

void calc(float p[][3], int npoints, trans t){

	getcorn(p, npoints, t);

	for(int i=0; i<t.count; i++){
		switch(t.order[i]){
			case 1:{ transpose(t, p, npoints); break; }
			case 2:{ scale(t, p, npoints); break; }
			case 3:{ rotat(t, p, npoints); break; }
			case 4:{ mirror(t, p, npoints); break; }
			case 5:{ shear(t, p, npoints); break; }
			default: break;
		}
	}
}

void getcorn(float p[][3], int npoints, trans t){
	
	if(t.useP == false){
		float x = p[0][0], y = p[0][1];
		for(int i=1; i<npoints; i++){
			if(y > p[i][1]){  y = p[i][1]; x = p[i][0]; }
			else if(y == p[i][1]){ if(x > p[i][0]) x = p[i][0]; }
		}
		t.point[0] = x; t.point[1] = y;
	}	
}

void write(float p[][3], int n){
	cout<<endl;
	for(int i=0; i<n; i++){
		cout << "(" << setw(5) << setprecision(3) << left << p[i][0] <<", ";
		cout << setw(5) << setprecision(3) << left << p[i][1] << ")" <<endl;
	}
}

void transpose(trans t, float p[][3], int n){
	
	float a[3][3] = {{1, 0, 0},{0, 1, 0},{0, 0, 1}};
	
	if(t.Tx_istrue == true) a[2][0] = t.T[0];
	if(t.Ty_istrue == true) a[2][1] = t.T[1];
	multiply(p, a, n);
}

void scale(trans t, float p[][3], int n){
	
	float a[3][3] = {{1, 0, 0},{0, 1, 0},{0, 0, 1}};

	a[2][0] = -1 * t.point[0];
	a[2][1] = -1 * t.point[1];
	multiply(p, a, n);
	a[2][0] = 0;	a[2][1] = 0;
	if(t.Sx_istrue == true) a[0][0] = t.S[0];
	if(t.Sy_istrue == true) a[1][1] = t.S[1];
	multiply(p, a, n);
	a[0][0] = 1;	a[1][1] = 1;
	a[2][0] = t.point[0];
	a[2][1] = t.point[1];
	multiply(p, a, n);
}

void rotat(trans t, float p[][3], int n){
	
	float a[3][3] = {{1, 0, 0},{0, 1, 0},{0, 0, 1}};

	a[2][0] = -1 * t.point[0];
	a[2][1] = -1 * t.point[1];
	multiply(p, a, n);
	a[2][0] = 0;	a[2][1] = 0;
	if(t.R_istrue == true){
		a[0][0] = roundf(cos(t.R * PI / 180.0) * 10000) / 10000;
		a[0][1] = roundf(sin(t.R * PI / 180.0) * 10000) / 10000;
		a[1][0] = -1 * a[0][1];
		a[1][1] = a[0][0];	
	}
	multiply(p, a, n);
	a[0][0] = 1; a[0][1] = 0; a[1][0] = 0; a[1][1] = 1;
	a[2][0] = t.point[0];
	a[2][1] = t.point[1];
	multiply(p, a, n);
}

void mirror(trans t, float p[][3], int n){
	
	float a[3][3] = {{1, 0, 0},{0, 1, 0},{0, 0, 1}};
	
	if(t.Mx_istrue == true && t.My_istrue == true && t.M[0] == 0 && t.M[1] == 0){
		a[1][1] = -1;		
		a[0][0] = -1;
		multiply(p, a, n);
		a[0][0]	= 1; a[1][1] = 1;
	}
	if(t.Mx_istrue == true && t.My_istrue == true && t.M[0] == 1 && t.M[1] == 1){
		a[0][0] = 0; a[0][1] = 1; a[1][0] = 1; a[1][1] = 0;
		multiply(p, a, n);
		a[0][0] = 1; a[0][1] = 0; a[1][0] = 0; a[1][1] = 1;
	}
	if(t.Mx_istrue == true && t.My_istrue == false){
		a[2][0] = t.M[0];
		a[0][0] = -1;
		multiply(p, a, n);
		a[0][0]	= 1;
		multiply(p, a, n);
		a[2][0] = 0;
	}
	if(t.My_istrue == true && t.Mx_istrue == false){
		a[2][1] = t.M[1];
		a[1][1] = -1;
		multiply(p, a, n);
		a[1][1]	= 1;
		multiply(p, a, n);
		a[2][1] = 0;
	}	
}

void shear(trans t, float p[][3], int n){
	
	float a[3][3] = {{1, 0, 0},{0, 1, 0},{0, 0, 1}};

	a[2][0] = -1 * t.point[0];
	a[2][1] = -1 * t.point[1];
	multiply(p, a, n);
	a[2][0] = 0;	a[2][1] = 0;
	if(t.Lx_istrue == true) a[1][0] = t.L[0];
	if(t.Ly_istrue == true) a[0][1] = t.L[1];
	multiply(p, a, n);
	a[1][0] = 0;	a[0][1] = 0;
	a[2][0] = t.point[0];
	a[2][1] = t.point[1];
	multiply(p, a, n);
}
