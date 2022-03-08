bool rule1(bool E, bool S, bool V, bool N) {
	return (V == 1) && (E == 1);
}

bool rule2(bool E, bool S, bool V, bool N) {
	return !((E == 1 && V == 1) || (E == 0 && V == 0) || (S == 1 && N == 1));
}

bool rule3(bool E, bool S, bool V, bool N) {
	return !((E == 1 && V == 1) || S == 0 || N == 0);
}

bool rule4(bool E, bool S, bool V, bool N) {
	return (((S == 1) || (N == 1)) && !(E || V));
}

bool rule5(bool E, bool S, bool V, bool N) {
	return !(E || S || V || N);
}

int funcEW(bool E, bool S, bool V, bool N, int *rule) {
	if (rule1(E, S, V, N)) {
		*rule = 1;
		return 1;
	} else if (rule2(E, S, V, N)) {
		*rule = 2;
		return 1;
	} else if (rule5(E, S, V, N)){
		*rule = 5;
		return 1;
	}
	return 0;
}

int funcNS(bool E, bool S, bool V, bool N, int *rule) {
	if (rule3(E, S, V, N)) {
		*rule = 3;
		return 1;
	} else if (rule4(E, S, V, N)) {
		*rule = 4;
		return 1;
	}
	return 0;
}

void openCloseSem(int *rule, bool *EW, bool *NS) {
	if (*rule == 1 || *rule == 2 || *rule == 5) {
		*EW = 1;
		*NS = 0;
	} else {
		*EW = 0;
		*NS = 1;
	}
}

void bigFunc(bool E, bool S, bool V, bool N, int *rule, bool *EW, bool *NS) {
	funcEW(E, S, V, N, rule);
	funcNS(E, S, V, N, rule);
	openCloseSem(rule, EW, NS);
}

void Tema1Func(bool E, bool S, bool V, bool N, int *rule, bool *EW, bool *NS) {
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE ap_none port=E
	#pragma HLS INTERFACE ap_none port=S
	#pragma HLS INTERFACE ap_none port=V
	#pragma HLS INTERFACE ap_none port=N
	bigFunc(E, S, V, N, rule, EW, NS);

}
