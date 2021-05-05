//Example of interacting with user LEDs
//Iran Arane Melchor Uceda
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED{
	private:
		string path;
		int number;
		virtual void writeLED(string fileName, string value);
		virtual void removeTrigger();

	public:
		LED(int number);
		virtual void turnOn();
		virtual void turnOff();
		virtual void flash (string delayms);
		virtual ~LED();

};

LED::LED(int number ){
	this ->number = number;
	ostringstream ledString;
	ledString << LED_PATH << number;
	path= string(ledString.str());
}

void LED::writeLED(string fileName, string value){
	ofstream fs;
	fs.open((path + fileName) .c_str());
	fs<<value;
	fs.close();
}

void LED:: removeTrigger(){
writeLED("/triger", "none");
}

void LED::turnOn(){
	cout << "LED" <<number << " on" <<endl;
	removeTrigger();
	writeLED("/brightness", "1");
}

void LED::turnOff(){
	cout <<"LED" << number << " off" <<endl;
	removeTrigger();
	writeLED("/brightness", "0");
}

void LED::flash(string delayms ="100"){
	cout << "Making LED" << number << " flash" << endl;
       	writeLED("/trigger", "timer");
	writeLED("/brightness", delayms);
	writeLED("/brightness", delayms);
}

LED::~LED(){
	cout << "removing LED" << number << endl;
}


//Main function:
int main(int argc, char* argv[]){
	if(argc!=2){
		cout << "Error" << endl;
		return 2;
	}
	cout << "Starting LED App" << endl;
	string cmd(argv[1]);
	LED leds[4]= { LED(0), LED(1), LED(2), LED(3)};
	for (int i=0; i<=3; i++){
		if (cmd=="on")
			leds[i].turnOn();
		else if(cmd=="off")
			leds[i].turnOff();
		else if (cmd=="flash")
			leds[i].flash();
		else
			cout << "Wrong command passed!! " << endl;
	}
	cout << "Finish the program" << endl;
	return 0;
}
