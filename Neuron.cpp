#include "Neuron.hpp"
#include <cmath>

//Constructeur et destructeur
Neuron::Neuron(double potential)
:V(potential), spikesNumber(0.0), refractory_time(0), clock(0)
{
	spikesTime.clear(); //To be sure that when we create a neuron it has got no spikes time 
}
Neuron::~Neuron(){}
		
//Getters
double Neuron::getPotential() const{
	return V;
}
double Neuron::getResistance() const{
	return R;
}
unsigned int Neuron::getSpikesNumber() const{
	return spikesNumber;
}
std::vector<double> Neuron::getSpikesTime() const{
	return spikesTime;
}


bool Neuron::isRefractory(){
	if(refractory_time> 0.0){
	return true;
	}
	return false;
}
		
//Update
void Neuron::update(double I){
	if(isRefractory()){ //If neuron is refractory -> neuron has spiked -> V is not modified
		refractory_time-=step;//Decrementation of the refractory time 
	}else{
		const double e(exp(-(h/tau)));
		double V_new(e*V+I*R*(1-e));
			
		if(V_new > V_th){
			spikesTime.push_back(clock); 
			spikesNumber+=1;
			refractory_time=tau_ref/h; //Initialisation of the refractory time 
			V_new=V_reset; //After  a spike, the potential gets back to its reset value
				
		}
		V=V_new; //modify neuron potential
	}
	++clock;	
}
