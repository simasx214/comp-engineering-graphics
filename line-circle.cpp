/*
  Simonas Paulikas, VGTU ELF Ef-15/2 
  Line and circle rasterizing implementation in C++ (Interface in LT)
*/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

void circle(int r, int x0, int y0, int oct);
void remap(int x0, int y0, int oct, int x, int y);
void line(int x0, int y0, int xg, int yg, int &lenght, int coords[][2]);
void remapln(int x, int y, int dir, float a, int lenght, int coords[][2], bool mode);
void read(int r, int x0, int y0, int oct, int xg, int yg, int lenght, int coords[][2]);

int main(){
	system("chcp 1257");
	
	int r, x0, y0, oct, xg, yg, lenght = 0;
	int coords[100][2];						//butu galima naudot dinaminius masyvus arba vektorius
	
    read(r, x0, y0, oct, xg, yg, lenght, coords);
	system("PAUSE");
	return 0;
}
void read(int r, int x0, int y0, int oct, int xg, int yg, int lenght, int coords[][2]){

    char choose;
		
	while(choose != 'a' || choose != 'b'){
		cout << "Pasirinkite rasterizavimo objektą: \n a Apskritimas.\n b Linija. \n";
		cin >> choose;
		if(choose == 'a' || choose == 'b') break;
	}
	
	switch (choose){
		case 'a' : {
			cout << "\nĮveskite spindulį: ";
			cin >> r;
			cout << "\nĮveskite apskritimo vidurio taško koordinates: ";
			cout << "\nX= ";
			cin >> x0;
			cout << "Y= ";
			cin >> y0;
			while(1){
			cout << "\nNurodykite aštuntadalio pradžios laipsnius: ";
			cin >> oct;
			if(oct == 0 || oct == 45 || oct == 90 || oct == 135 || oct == 180 ||
			   oct == 225 || oct == 270 || oct == 315) break;
			}
			cout << endl;
			
			circle(r, x0, y0, oct);
			
			break;
		}
		case 'b' : {
			cout << "\nĮveskite pradines koordinates: ";
			cout << "\nX= ";
			cin >> x0;
			cout << "Y= ";
			cin >> y0;
			cout << "Įveskite galines koordinates: ";
			cout << "\nX= ";
			cin >> xg;
			cout << "Y= ";
			cin >> yg;
			cout << endl;
			
			line(x0, y0, xg, yg, lenght, coords);
			
			break;
		}
	}
}
void circle(int r, int x0, int y0, int oct){
	int p;
	int x = 0, y = r;
	
	p = 1- r;
//	cout << x << ", " << y <<endl;			//debug purposes
	
	while (x < y){
		
		if(p < 0){
			p = p + (2 * x + 2) + 1;
			x++;
		}
		else if(p >= 0){
			p = p + (2 * x + 2) + 1 - (2 * y - 2);
			x++;
			y--;
		}
		remap(x0, y0, oct, x, y);
	}
	
}

void remap(int x0, int y0, int oct, int x, int y){
	
	int temp;
	switch(oct){
		
		case 0 : {
			temp = x;
			x = y + y0;
			y = temp + x0;
			break;
		}
		case 45 : {
			x = x + x0;
			y = y + y0;
			break;
		}
		case 90 : {
			x = -1 * x + x0;
			y = y + y0;
			break;
		}
		case 135 : {
			temp = x;
			x = -1 * y + y0;
			y = temp + x0;
			break;
		}
		case 180 : {
			temp = x;
			x = -1 * y + y0;
			y = -1 * temp + x0;
			break;
		}
		case 225 : {
			x = -1 * x + x0;
			y = -1 * y + y0;
			break;
		}
		case 270 : {
			x = x + x0;
			y = -1 * y + y0;
			break;
		}
		case 315 : {
			temp = x;
			x = y + y0;
			y = -1 * temp + x0;
			break;
		}
		default : {
			cout << "Nurodytas netinkamas aštuntadalis. ";
			break;
		}			
	}	
	cout << "x= " << x << ", y= " << y <<endl;
}

void line(int x0, int y0, int xg, int yg, int &lenght, int coords[][2]){
	int x, y, dy, dx, xs, ys;
	int d, temp, dir = 1;
	float a;
		
	x = x0;
	y = y0;
	xs = xg;
	ys = yg;
	dy = yg - y;
	dx = xg - x;

	a = (float)dy/(float)dx;
//	cout << a <<endl; //debug purposes
	cout << "x= " << x << ", y= " << y <<endl;
	if(a > 1){
		temp = x;
		x = y;
		y = temp;
		temp = xg;
		xg = yg;
		yg = temp;
	}
	else if(a < -1){
		temp = x;
		x = y;
		y = -1 * temp;
		temp = xg;
		xg = yg;
		yg = -1 * temp;
	}
	else if(a >= -1 && a <= 0){
		x = -1 * x;
	}
	if(x > xg && y > yg){
			temp = xg;
			xg = x;
			x = temp;
			temp = yg;
			yg = y;
			y = temp;
			dir = -1;
	}
	dy = yg - y;
	dx = xg - x;
	d = 2 * dy - dx;
	while(x < xg || y < yg){
		//dy = yg - y;
		//dx = xg - x;
		if(d > 0){
			x++;
			y++;
			d = d + 2 * (dy - dx);
		}
		else if (d <= 0){
			x++;
			d = d + (2 * dy);
		}
		lenght++;
		remapln(x, y, dir, a, lenght, coords, 0);
		//cout << "x= " << x << ", y= " << y <<endl;
	}
	remapln(x, y, dir, a, lenght, coords, 1);
}

void remapln(int x, int y, int dir, float a, int lenght, int coords[][2], bool mode){

	int temp;
	
	if(mode == 0){	
	coords[lenght-1][0] = x;
	coords[lenght-1][1] = y; 
	}
	
	else if(mode == 1){
		if(dir == -1){
			for(int i=0; i < (lenght/2); ++i){
				temp = coords[i][0];
				coords[i][0] = coords[lenght-i-1][0];
				coords[lenght-i-1][0] = temp;
				
				temp = coords[i][1];
				coords[i][1] = coords[lenght-i-1][1];
				coords[lenght-i-1][1] = temp;
			}
		}
		if(a >= 0 && a <= 1){
			
		}
		else if(a > 1){
			for(int i = 0; i < lenght; i++){
				temp = coords[i][0];
				coords[i][0] = coords[i][1];
				coords[i][1] = temp;	
			}
		}
		else if(a < -1){
			for(int i = 0; i < lenght; i++){
				temp = -1 * coords[i][1];
				coords[i][1] = coords[i][0];
				coords[i][0] = temp;	
			}
		}
		else if(a >= -1 && a <= 0)	{
			for(int i = 0; i < lenght; i++){
				coords[i][0] = -1 * coords[i][0];
			}
		}
		for(int i = 0; i < lenght; i++){
				cout << "x= "<< coords[i][0] <<" , y= "<< coords[i][1] <<endl;
		}
	}
}
