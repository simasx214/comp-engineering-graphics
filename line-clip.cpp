/*  Simonas Paulikas, VGTU ELF Ef-15/2
    Line clipping using Cohen-Sutherland algorithm (Interface in LT)
*/
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MaxLine=5;

struct line{
    float x1, 
          y1,
          x2,
          y2,
		  xs1,
		  xs2,
		  ys1,
		  ys2;
    char code1[5],
         code2[5],
         code[5];      
};
line l[MaxLine];

void read(line l[], float limits[4], int &nline);
void calc(line l[], float limits[4], int nline);
void write(line l[], float limits[4], int nline);


int main(){
	int nline;
	float limits[4];

	
	read(l, limits, nline);
	calc(l, limits, nline);
	write(l,limits, nline);

return 0;
}

void read(line l[], float limits[4], int &nline){
	
	cout << "Iveskite ribas." <<endl;
	cout << "Xmin: ";
	cin >> limits[0];
	cout << "\nXmax: ";
	cin >> limits[1];
	cout << "\nYmin: ";
	cin >> limits[2];
	cout << "\nYmax: ";
	cin >> limits[3];
	
	cout << "\n\nKiek atkarpu ivesite? (max " << MaxLine << "): ";
	cin >> nline;
	
	for(int i=0; i<nline; i++){
		cout <<"\n\nIveskite "<< i+1 << " atkarpos galu koordinates:"<<endl;
		cout <<"X1: ";
		cin >> l[i].x1;
		cout <<"Y1: ";
		cin >> l[i].y1;
		cout <<"X2: ";
		cin >> l[i].x2;
		cout <<"Y2: ";
		cin >> l[i].y2;
	}
}

void calc(line l[], float limits[4], int nline){
	
	float x, y, t, tmpx1, tmpx2, tmpy1, tmpy2;
	char axis;
	
	for(int loop=0; loop<nline; loop++){
		
		if(l[loop].x1 < limits[0]) l[loop].code1[3]='1';
		else l[loop].code1[3]='0';
		if(l[loop].x2 < limits[0]) l[loop].code2[3]='1';
		else l[loop].code2[3]='0';
		
		if(l[loop].x1 > limits[1]) l[loop].code1[2]='1';
		else l[loop].code1[2]='0';
		if(l[loop].x2 > limits[1]) l[loop].code2[2]='1';
		else l[loop].code2[2]='0';
		
		if(l[loop].y1 < limits[2]) l[loop].code1[1]='1';
		else l[loop].code1[1]='0';
		if(l[loop].y2 < limits[2]) l[loop].code2[1]='1';
		else l[loop].code2[1]='0';
		
		if(l[loop].y1 > limits[3]) l[loop].code1[0]='1';
		else l[loop].code1[0]='0';
		if(l[loop].y2 > limits[3]) l[loop].code2[0]='1';
		else l[loop].code2[0]='0';
		l[loop].code1[4]='\0';
		l[loop].code2[4]='\0';
		l[loop].code[4]='\0';
		l[loop].xs1=-100;
		l[loop].xs2=-100;
		l[loop].ys1=-100;
		l[loop].ys2=-100;
		//for(int i=0; i<4; i++)
		//cout << "\n"<< l[loop].code1;
		//cout << "\n"<< l[loop].code2;
		
		for(int i=0; i<4; i++){
			if((l[loop].code1[i] == '1') && (l[loop].code2[i] == '1')) l[loop].code[i] = '1';
			else l[loop].code[i] = '0';
		}
		//cout << "\n"<< l[loop].code;
		if(l[loop].code[0] == '0' && l[loop].code[1] == '0' && l[loop].code[2] == '0' && l[loop].code[3] == '0'){
			if(l[loop].code1[0] == '0' || l[loop].code1[1] == '0' || l[loop].code1[2] == '0' || l[loop].code1[3] == '0'){ tmpx1 = l[loop].x1; tmpy1 = l[loop].y1;}
			if(l[loop].code2[0] == '0' || l[loop].code2[1] == '0' || l[loop].code2[2] == '0' || l[loop].code2[3] == '0'){ tmpx2 = l[loop].x2; tmpy2 = l[loop].y2;}
			 
			while(l[loop].code1[0] != '0' || l[loop].code1[1] != '0' || l[loop].code1[2] != '0' || l[loop].code1[3] != '0'){
				if(l[loop].code1[0] == '1'){ y=limits[3]; axis = 'Y';}
				else if(l[loop].code1[1] == '1'){ y=limits[2]; axis = 'y';}
				else if(l[loop].code1[2] == '1'){ x=limits[1]; axis = 'X';}
				else if(l[loop].code1[3] == '1'){ x=limits[0]; axis = 'x';}
				
				if(axis == 'Y' || axis == 'y'){
					t = (y-l[loop].y1)/(l[loop].y2-l[loop].y1);
					if(axis == 'Y'){ l[loop].code1[0] = '0'; if(t > 0 && t < 1) l[loop].xs2 = round( 10 * (t * (l[loop].x2-l[loop].x1) + l[loop].x1))/10; tmpx1 = l[loop].xs2;}
					else { l[loop].code1[1] = '0'; if(t > 0 && t < 1) l[loop].xs1 = round( 10 * (t * (l[loop].x2-l[loop].x1) + l[loop].x1))/10; tmpx1 = l[loop].xs1;}
					if(l[loop].xs1 < limits[0] || l[loop].xs1 > limits[1]) l[loop].xs1 = -100;
					if(l[loop].xs2 > limits[1] || l[loop].xs2 < limits[0]) l[loop].xs2 = -100;
					tmpy1 = y;
				}
				
				else if(axis == 'X' || axis == 'x'){
					t = (x-l[loop].x1)/(l[loop].x2-l[loop].x1);
					if(axis == 'X'){ l[loop].code1[2] = '0'; if(t > 0 && t < 1) l[loop].ys2 = round( 10 * (t * (l[loop].y2-l[loop].y1) + l[loop].y1))/10; tmpy1 = l[loop].ys2;}
					else { l[loop].code1[3] = '0'; if(t > 0 && t < 1) l[loop].ys1 = round( 10 * (t * (l[loop].y2-l[loop].y1) + l[loop].y1))/10; tmpy1 = l[loop].ys1;}
					if(l[loop].ys1 < limits[2] || l[loop].ys1 > limits[3]) l[loop].ys1 = -100;
					if(l[loop].ys2 > limits[3] || l[loop].ys2 < limits[2]) l[loop].ys2 = -100;
					tmpx1 = x;
				}
				
				
			}
			while(l[loop].code2[0] != '0' || l[loop].code2[1] != '0' || l[loop].code2[2] != '0' || l[loop].code2[3] != '0'){
				if(l[loop].code2[0] == '1'){ y=limits[3]; axis = 'Y';}
				else if(l[loop].code2[1] == '1'){ y=limits[2]; axis = 'y';}
				else if(l[loop].code2[2] == '1'){ x=limits[1]; axis = 'X';}
				else if(l[loop].code2[3] == '1'){ x=limits[0]; axis = 'x';}
			
				if(axis == 'Y' || axis == 'y'){
					t = (y-l[loop].y1)/(l[loop].y2-l[loop].y1);
					if(axis == 'Y'){ l[loop].code2[0] = '0'; if(t > 0 && t < 1) l[loop].xs2 = round( 10 * (t * (l[loop].x2-l[loop].x1) + l[loop].x1))/10; tmpx2 = l[loop].xs2;}
					else { l[loop].code2[1] = '0'; if(t > 0 && t < 1) l[loop].xs1 = round( 10 * (t * (l[loop].x2-l[loop].x1) + l[loop].x1))/10; tmpx2 = l[loop].xs1;}
					if(l[loop].xs1 < limits[0] || l[loop].xs1 > limits[1]) l[loop].xs1 = -100;
					if(l[loop].xs2 > limits[1] || l[loop].xs2 < limits[0]) l[loop].xs2 = -100;
					tmpy2 = y;
				}
				else if(axis == 'X' || axis == 'x'){
					t = (x-l[loop].x1)/(l[loop].x2-l[loop].x1);
					if(axis == 'X'){ l[loop].code2[2] = '0'; if(t > 0 && t < 1) l[loop].ys2 = round( 10 * (t * (l[loop].y2-l[loop].y1) + l[loop].y1))/10; tmpy2 = l[loop].ys2;}
					else { l[loop].code2[3] = '0'; if(t > 0 && t < 1) l[loop].ys1 = round( 10 * (t * (l[loop].y2-l[loop].y1) + l[loop].y1))/10; tmpy2 = l[loop].ys1;}
					if(l[loop].ys1 < limits[2] || l[loop].ys1 > limits[3]) l[loop].ys1 = -100;
					if(l[loop].ys2 > limits[3] || l[loop].ys2 < limits[2]) l[loop].ys2 = -100;
					tmpx2 = x;
				}
			}
		//cout << l[loop].x1 << " " << l[loop].x2 << "; " << l[loop].y1 << " " << l[loop].y2 << "\n";
		//cout << l[loop].xs1 << " " << l[loop].xs2 << "; " << l[loop].ys1 << " " << l[loop].ys2 << "\n";
		//system("PAUSE");
			l[loop].x1 = tmpx1; l[loop].x2 = tmpx2; l[loop].y1 = tmpy1; l[loop].y2 = tmpy2; 
		}
	}
}

void write(line l[], float limits[4], int nline){
	
	cout <<endl;
	for(int loop=0; loop<nline; loop++){
		if(l[loop].code[0] == '0' && l[loop].code[1] == '0' && l[loop].code[2] == '0' && l[loop].code[3] == '0'){
			cout << loop+1 << " atkarpos taskai: ";
			cout << "(" << l[loop].x1 <<", " << l[loop].y1 << "), (" << l[loop].x2 <<", " << l[loop].y2 << ")" <<endl;
		}
		else cout << loop+1 << " atkarpa nematoma.\n";
	}
}
