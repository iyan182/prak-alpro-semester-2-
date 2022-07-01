#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

string kondisi(string player, string lawan)
{
	if (player == "Batu")
	{
		if (lawan == "Batu") //Function
		{
			return "Seri";
		}
		else if (lawan == "Gunting") //Function
		{
			return "Menang";
		}
		else if (lawan == "Kertas") //Function
		{
			return "Kalah";
		}
	}
	else if (player == "Gunting")
	{
		if (lawan == "Batu") //Function
		{
			return "Kalah";
		}
		else if (lawan == "Gunting") //Function
		{
			return "Seri";
		}
		else if (lawan == "Kertas") //Function
		{
			return "Menang";
		}
	}
	else if (player == "Kertas")
	{
		if (lawan == "Batu") //Function
		{
			return "Menang";
		}
		else if (lawan == "Gunting") //Function
		{
			return "Kalah";
		}
		else if (lawan == "Kertas") //Function
		{
			return "Seri";
		}
	}
}

void TampilHasil(string player, string lawan)
{
	string hasil = kondisi(player, lawan);
	cout<< "Anda Dinyatakan "<<hasil<<endl;
}

struct perulangan //St
{
	string ulang;
};

int main() 
{
	perulangan perulangan;
	
	string akhir = "Program Game Selesai";
	string *akhir2 = &akhir; //Pointer
	
	string isi[3] = {"Batu", "Gunting", "Kertas"};
	int pilihan, lawan;
	
	do{ //Looping
		system("cls");
		for(int a = 0; a < 3; a++) //Matrix
		{
			cout<<a+1<<". "<<isi[a]<<endl;
		}
		cout<<"\nPilihan : "; cin>>pilihan;
		lawan = (rand() % 3) + 1; 
		cout<<"Lawan : "<<lawan<<endl;
		cout<<"\n===================="<<endl;
		cout<<"Player : "<<isi[pilihan-1]<<endl;
		cout<<"Lawan  : "<<isi[lawan-1]<<endl;
		TampilHasil(isi[pilihan-1], isi[lawan-1]);
		cout<<"\nMain Lagi ? <Y/N> : "; cin>>perulangan.ulang;
	} while(perulangan.ulang == "Y");
	system("cls");
	cout<<*akhir2<<endl;
}
