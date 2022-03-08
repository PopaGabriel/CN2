#include <iostream>
#include "tema1Curs_tb.h"

int main() {
	bool E, S, V, N, NS, EW;
	int rule;
	for (int iV = 0; iV < 2; iV++)
		for (int iE = 0; iE < 2; iE++)
			for (int iN = 0; iN < 2; iN++)
				for (int iS = 0; iS < 2; iS++){
					Tema1Func(iE, iS, iV, iN, &rule, &EW, &NS);
					std::cout<< iV << " "<< iE << " " << iN << " " << iS << " " << rule << " "
							<< EW << " "<<NS<<std::endl;
				}

	return 0;
}
