
#include <urbi/uobject.hh>
#include <urbi/uclient.hh>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

std::ofstream myfile;

//adquisicion del tiempo 
void getTime(double& tim)
{
	struct timespec tsp;
	clock_gettime(CLOCK_REALTIME, &tsp);   
	tim = (double)(tsp.tv_sec+ tsp.tv_nsec*0.000000001);
	return;
}
//escritura en archivo
void saveData( double tim,double value){
	myfile << tim;
	myfile << "\t";
	myfile << value;
	myfile << "\n";
	return;
}

//callback de URBI
urbi::UCallbackAction onJointSensor(const urbi::UMessage &msg) 
  {
	double value = (double)msg.value->val;
	if (msg.tag=="legRF1")
		double tim;
		getTime(tim);
		saveData(tim,value);
	return urbi::URBI_CONTINUE;
  }
  
 
int main(int argc, char** argv)
{
	//inicializacion del cliente URBI
	urbi::UClient* client = new urbi::UClient(argv[1], 54000);
	//inicializacion del callback
	client->setCallback (urbi::callback(onJointSensor),"legRF1");
	//demanda del bucle de envio
	client->send("loop legRF1 << legRF1.val,");
	//abre el archivo de escritura
	myfile.open ("Data1.txt");
	myfile.precision(15);
	//bucle de URBI
	urbi::execute();
	//cierra el archivo de escritura
	myfile.close();
	return(0);
}
