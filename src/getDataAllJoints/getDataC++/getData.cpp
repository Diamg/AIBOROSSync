
#include <urbi/uobject.hh>
#include <urbi/uclient.hh>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

std::ofstream myfile;

void getTime(double& tim)
{

   struct timespec tsp;

   clock_gettime(CLOCK_REALTIME, &tsp);   //Call clock_gettime to fill tsp
	
   
   tim = (double)(tsp.tv_sec+ tsp.tv_nsec*0.000000001);
  
	return;
}
void saveData( double tim,double value, std::string tag ){
	
	
	myfile << tim;
	myfile << "\t";
	myfile << tag;
	myfile << "\t";
	myfile << value;
	myfile << "\n";
	return;
}
urbi::UCallbackAction onJointSensor(const urbi::UMessage &msg) 
  {
	double value = (double)msg.value->val;
	std::cout << value <<std::flush;
	std::cout << "\n"<<std::flush;
	std::cout.precision(18);		
	double tim;
		
	getTime(tim);
	std::cout << tim <<std::flush;
	std::cout << "\n" <<std::flush;
	saveData(tim,value, msg.tag);
		

	return urbi::URBI_CONTINUE;
  }
int main(int argc, char** argv)
{
	urbi::UClient* client = new urbi::UClient(argv[1], 54000);
	std::cout << "start"<<std::flush;
	client->setCallback (urbi::callback(onJointSensor),"legRF1");
	client->setCallback (urbi::callback(onJointSensor),"legRF2");
	client->setCallback (urbi::callback(onJointSensor),"legRF3");
	client->setCallback (urbi::callback(onJointSensor),"legRH1");
	client->setCallback (urbi::callback(onJointSensor),"legRH2");
	client->setCallback (urbi::callback(onJointSensor),"legRH3");
	client->setCallback (urbi::callback(onJointSensor),"legLF1");
	client->setCallback (urbi::callback(onJointSensor),"legLF2");
	client->setCallback (urbi::callback(onJointSensor),"legLF3");
	client->setCallback (urbi::callback(onJointSensor),"legLH1");
	client->setCallback (urbi::callback(onJointSensor),"legLH2");
	client->setCallback (urbi::callback(onJointSensor),"legLH3");
	client->setCallback (urbi::callback(onJointSensor),"mouth");
	client->setCallback (urbi::callback(onJointSensor),"headNeck");
	client->setCallback (urbi::callback(onJointSensor),"headPan");
	client->setCallback (urbi::callback(onJointSensor),"headTilt");
	client->setCallback (urbi::callback(onJointSensor),"tailTilt");
	client->setCallback (urbi::callback(onJointSensor),"tailPan");


	client->send("loop legRF1 << legRF1.val, loop legRF2 << legRF2.val, loop legRF3 << legRF3.val, loop legRH1 << legRH1.val, loop legRH2 << legRH2.val, loop legRH3 << legRH3.val, loop legLF1 << legLF1.val, loop legLF2 << legLF2.val, loop legLF3 << legLF3.val, loop legLH1 << legLH1.val, loop legLH2 << legLH2.val, loop legLH3 << legLH3.val, loop neck << neck.val, loop headTilt << headTilt.val, loop headPan << headPan.val, loop tailPan << tailPan.val, loop tailTilt << tailTilt.val, loop mouth << mouth.val,");
	std::cout << "send"<<std::flush;
	myfile.open ("Data1.txt");
	myfile.precision(15);
	urbi::execute();
	myfile.close();

	std::cout << "finish"<<std::flush;

	return(0);
}
