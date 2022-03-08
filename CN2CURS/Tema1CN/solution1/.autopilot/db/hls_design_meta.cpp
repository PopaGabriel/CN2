#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("E", 1, hls_in, 0, "ap_none", "in_data", 1),
	Port_Property("S", 1, hls_in, 1, "ap_none", "in_data", 1),
	Port_Property("V", 1, hls_in, 2, "ap_none", "in_data", 1),
	Port_Property("N", 1, hls_in, 3, "ap_none", "in_data", 1),
	Port_Property("rule", 32, hls_in, 4, "ap_none", "in_data", 1),
	Port_Property("EW", 1, hls_in, 5, "ap_none", "in_data", 1),
	Port_Property("NS", 1, hls_in, 6, "ap_none", "in_data", 1),
};
const char* HLS_Design_Meta::dut_name = "Tema1Func";
