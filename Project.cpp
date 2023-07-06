#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <string>
using namespace std;

void selection(int arr[], int size);


void selection(int arr[], int size){
	int pos_min;
	int temp; 
	
	for (int i=0; i<size-1; i++){
		pos_min = i;
		for(int j=i+1; j<size; j++){
			if(arr[j] < arr[pos_min]){
				pos_min = j;
			}
		}
		if (pos_min != i){
			temp = arr[i];
			arr[i] = arr[pos_min];
			arr[pos_min] = temp;	
		}
	}
}

struct WIFI{
	string Channel;
	string Ssid;
	string Bssid;
	string Authentication;
	string Encryption;//"NONE" for open network
	string SignalStrength; // from 0 to 100
	int SignalStrength_Int = atoi(SignalStrength.c_str());
	string WirelessMode; 
	string Ext_ch;
	string Gps;
};

bool WIFIcompare(WIFI lhs, WIFI rhs){
	return lhs.SignalStrength_Int < rhs.SignalStrength_Int;
}

int main(){
	ifstream ip("wifi_info.csv");
	ofstream op("wifi_info.txt");
	
	string channel;
	string ssid;
	string bssid;
	string authentication;
	string encryption;//"NONE" for open network
	string signalStrength; // from 0 to 100
	string wirelessMode; 
	string ext_ch;
	string gps;
	int signalStrength_Int;
	int index = 0;
	
	op <<"Error: Cannot retrieve gps Information. "<< '\n'<<endl;

	while(ip.good()){
		
		getline(ip,channel,',');
		if(channel.empty())
		{
			return -1;
		}
		getline(ip,ssid,',');
		getline(ip,bssid,',');
		getline(ip,authentication,',');
		getline(ip,encryption,',');
		getline(ip,signalStrength,',');
		signalStrength_Int= atoi(signalStrength.c_str());
		
		if(signalStrength_Int > 100 || signalStrength_Int < 0){
			return -1;
		}
		
		getline(ip,wirelessMode,',');
		getline(ip,ext_ch,',');
		getline(ip,gps,'\n');
		
		WIFI a[50];
		a[index] = {channel, ssid, bssid, authentication, encryption, signalStrength, signalStrength_Int, wirelessMode, ext_ch, gps};
		
		cout <<"Wifi No." << index+1 <<":"<<endl;
		cout <<" channel: " << a[index].Channel <<endl;
		cout <<" ssid: " << a[index].Ssid <<endl;
		cout <<" bssid: " << a[index].Bssid <<endl;
		cout <<" authentication: " << a[index].Authentication <<endl;
		if(a[index].Encryption == "NONE")
		{
			cout <<" encryption: " << a[index].Encryption <<" (Warning: Wifi is not secured!)" <<endl;
		}
		else{
			cout <<" encryption: " << a[index].Encryption <<endl;
		}
		cout <<" signalStrength: " << a[index].SignalStrength<<endl;
		cout <<" wirelessMode: " << a[index].WirelessMode <<endl;
		cout <<" ext_ch: " << a[index].Ext_ch <<endl;
		
		op << "Wifi No." << index+1 <<":"<<endl;
		op <<" Channel: " << a[index].Channel <<endl;
		op <<" Name: " << a[index].Ssid <<endl;
		if(a[index].Encryption == "NONE")
		{
			op <<" Encryption: " << a[index].Encryption <<" (Public)" <<endl;
		}
		else{
			op <<" Encryption: " << a[index].Encryption <<" (Private)"<<endl;
		}
		if(signalStrength_Int == 100){	
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Perfect)"<<endl;
		}
		else if(signalStrength_Int == 0){
			op <<" SignalStrength: " << a[index].SignalStrength<<" (No Signal)"<<endl;
		}
		else if(signalStrength_Int < 100 && signalStrength_Int >= 80){
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Great)"<<endl;
		}
		else if(signalStrength_Int < 80 && signalStrength_Int >= 60){
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Good)"<<endl;
		}
		else if(signalStrength_Int < 60 && signalStrength_Int >= 40){
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Fair)"<<endl;
		}
		else if(signalStrength_Int < 40 && signalStrength_Int >= 20){
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Bad)"<<endl;
		}
		else{
			op <<" SignalStrength: " << a[index].SignalStrength<<" (Poor)"<<endl;	
		index++;	
		}
	}
		
	ip.close();		
	op.close();
	return 0;
}
