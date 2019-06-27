#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NEURONS 	4
#define HIDDEN_NEURONS	3
#define OUTPUT_NEURONS	4

double wih[INPUT_NEURONS+1][HIDDEN_NEURONS]

double who[HIDDEN_NEURONS+1][OUTPUT_NEURONS]

double inputs[INPUT_NEURONS]
double hidden[HIDDEN_NEURONS]
double target[OUTPUT_NEURONS]
double actual[OUTPUT_NEURONS]

double erro[OUTPUT_NEURONS]
double errh[HIDDEN_NEURONS]

#define LEARN_RATE	0.2
#define RAND_WEIGHT	(((float)rand() / (float)RAND_MAX) - 0.5)
#define getSRand() ((float)rand() / (float)RAND_MAX)
#define getRand(x) (int)((x)*getSRand())
#define sqr(x) ((x) * (x))

void assgnRandomWeights(void){
	int hid, inp, out;
	
	for(inp = 0; inp < INPUT_NEURONS+1; inp++){
		for (hid = 0; hid < HIDDEN_NEURONS+1; hid++){
			wih[inp][hid] = RAND_WEIGHT;
		}
	}
	
	for(hid = 0; hid < HIDDEN_NEURONS+1; hid++){
		for(out = 0; out < OUTPUT_NEURONS; out++){
			who[hid][out] = RAND_WEIGHT;
		}
	}
}

double sigmoid(double val){
	return (1.0 / (1.0 + exp(-val)));
}

double sigmoidDerivative(double val){
	return (val * (1.0 - val))
}

void feedForward(void){
}
