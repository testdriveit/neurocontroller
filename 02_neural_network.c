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
	int inp, hid, out;
	double sum;
	
	for (hid = 0; hid < HIDDEN_NEURONS; hid++){
		sum = 0.0;
		for (inp = 0; inp < INPUT_NEURONS; inp++){
			sum += inputs[inp]*wih[inp][hid];
		}
		
		sum += wih[INPUT_NEURONS][hid];
		hidden[hid] = sigmoid(sum);
	}
	
	for (out = 0; out < OUTPUT_NEURONS; out++){
		sum = 0.0;
		for (hid = 0; hid < HIDDEN_NEURONS; hid++) {
			sum += hidden[hid]*who[hid][out];
		}
		sum += who[HIDDEN_NEURONS][out];
		actual[out] = sigmoid(sum);
	}
}

void backPropagate(void){
	int inp, hid, out;
	
	for (out = 0; out < OUTPUT_NEURONS; out++){
		erro[out] = (target[out] - actual[out])*sigmoidDerivative(actual[out]);
	}
	
	for (hid = 0; hid < HIDDEN_NEURONS; hid++){
		errh[hid] = 0.0;
		for (out = 0; out < OUTPUT_NEURONS; out++){
			errh[hid] += erro[out]*who[hid][out];
		}
		errh[hid] *= sigmoidDerivative(hidden[hid]);
	}
	
	for (out = 0; out < OUTPUT_NEURONS; out++){
		for(hid = 0; hid < HIDDEN_NEURONS; hid++){
			who[hid][out] += (LEARN_RATE*erro[out]*hidden[hid]);
		}
		who[HIDDEN_NEURONS][out] += (LEARN_RATE*erro[out]);
	}
	
	for (hid = 0; hid < HIDDEN_NEURONS; hid++){
		for (inp = 0; inp < INPUT_NEURONS; inp++){
			wih[inp][hid] += (LEARN_RATE * errh[hid] * inputs[inp]);
		}
		wih[INPUT_NEURONS][hid] += (LEARN_RATE * errh[hid]);
	}
}
