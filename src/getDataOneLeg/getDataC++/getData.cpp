
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
void saveData( double tim,double value){
	
	
	myfile << tim;
	myfile << "\t";
	myfile << value;
	myfile << "\n";
	return;
}
urbi::UCallbackAction onJointSensor(const urbi::UMessage &msg) 
  {
	double value = (double)msg.value->val;
	if (msg.tag=="legRF1")
		
		std::cout << value <<std::flush;
		std::cout << "\n"<<std::flush;
		std::cout.precision(18);		
		double tim;
		
		getTime(tim);
		 std::cout << tim <<std::flush;
   std::cout << "\n" <<std::flush;
		saveData(tim,value);
		

	return urbi::URBI_CONTINUE;
  }
int main(int argc, char** argv)
{
	urbi::UClient* client = new urbi::UClient(argv[1], 54000);
	std::cout << "start"<<std::flush;
	client->setCallback (urbi::callback(onJointSensor),"legRF1");
	client->send("loop legRF1 << legRF1.val,");
	std::cout << "send"<<std::flush;
	myfile.open ("Data1.txt");
	myfile.precision(15);
	urbi::execute();
	myfile.close();

	std::cout << "finish"<<std::flush;

	return(0);
}
