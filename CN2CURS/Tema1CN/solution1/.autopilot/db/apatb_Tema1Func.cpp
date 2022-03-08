#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_E "../tv/cdatafile/c.Tema1Func.autotvin_E.dat"
#define AUTOTB_TVOUT_E "../tv/cdatafile/c.Tema1Func.autotvout_E.dat"
// wrapc file define:
#define AUTOTB_TVIN_S "../tv/cdatafile/c.Tema1Func.autotvin_S.dat"
#define AUTOTB_TVOUT_S "../tv/cdatafile/c.Tema1Func.autotvout_S.dat"
// wrapc file define:
#define AUTOTB_TVIN_V "../tv/cdatafile/c.Tema1Func.autotvin_V.dat"
#define AUTOTB_TVOUT_V "../tv/cdatafile/c.Tema1Func.autotvout_V.dat"
// wrapc file define:
#define AUTOTB_TVIN_N "../tv/cdatafile/c.Tema1Func.autotvin_N.dat"
#define AUTOTB_TVOUT_N "../tv/cdatafile/c.Tema1Func.autotvout_N.dat"
// wrapc file define:
#define AUTOTB_TVIN_rule "../tv/cdatafile/c.Tema1Func.autotvin_rule.dat"
#define AUTOTB_TVOUT_rule "../tv/cdatafile/c.Tema1Func.autotvout_rule.dat"
// wrapc file define:
#define AUTOTB_TVIN_EW "../tv/cdatafile/c.Tema1Func.autotvin_EW.dat"
#define AUTOTB_TVOUT_EW "../tv/cdatafile/c.Tema1Func.autotvout_EW.dat"
// wrapc file define:
#define AUTOTB_TVIN_NS "../tv/cdatafile/c.Tema1Func.autotvin_NS.dat"
#define AUTOTB_TVOUT_NS "../tv/cdatafile/c.Tema1Func.autotvout_NS.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_E "../tv/rtldatafile/rtl.Tema1Func.autotvout_E.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_S "../tv/rtldatafile/rtl.Tema1Func.autotvout_S.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_V "../tv/rtldatafile/rtl.Tema1Func.autotvout_V.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_N "../tv/rtldatafile/rtl.Tema1Func.autotvout_N.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_rule "../tv/rtldatafile/rtl.Tema1Func.autotvout_rule.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_EW "../tv/rtldatafile/rtl.Tema1Func.autotvout_EW.dat"
// tvout file define:
#define AUTOTB_TVOUT_PC_NS "../tv/rtldatafile/rtl.Tema1Func.autotvout_NS.dat"

class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  E_depth = 0;
  S_depth = 0;
  V_depth = 0;
  N_depth = 0;
  rule_depth = 0;
  EW_depth = 0;
  NS_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{E " << E_depth << "}\n";
  total_list << "{S " << S_depth << "}\n";
  total_list << "{V " << V_depth << "}\n";
  total_list << "{N " << N_depth << "}\n";
  total_list << "{rule " << rule_depth << "}\n";
  total_list << "{EW " << EW_depth << "}\n";
  total_list << "{NS " << NS_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int E_depth;
    int S_depth;
    int V_depth;
    int N_depth;
    int rule_depth;
    int EW_depth;
    int NS_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};

static void RTLOutputCheckAndReplacement(std::string &AESL_token, std::string PortName) {
  bool no_x = false;
  bool err = false;

  no_x = false;
  // search and replace 'X' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('X', 0);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
  no_x = false;
  // search and replace 'x' with '0' from the 3rd char of token
  while (!no_x) {
    size_t x_found = AESL_token.find('x', 2);
    if (x_found != string::npos) {
      if (!err) { 
        cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' on port" 
             << PortName << ", possible cause: There are uninitialized variables in the C design."
             << endl; 
        err = true;
      }
      AESL_token.replace(x_found, 1, "0");
    } else
      no_x = true;
  }
}
extern "C" void Tema1Func_hw_stub_wrapper(char, char, char, char, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_Tema1Func_hw(char __xlx_apatb_param_E, char __xlx_apatb_param_S, char __xlx_apatb_param_V, char __xlx_apatb_param_N, volatile void * __xlx_apatb_param_rule, volatile void * __xlx_apatb_param_EW, volatile void * __xlx_apatb_param_NS) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static AESL_FILE_HANDLER aesl_fh;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
//E
aesl_fh.touch(AUTOTB_TVIN_E);
aesl_fh.touch(AUTOTB_TVOUT_E);
//S
aesl_fh.touch(AUTOTB_TVIN_S);
aesl_fh.touch(AUTOTB_TVOUT_S);
//V
aesl_fh.touch(AUTOTB_TVIN_V);
aesl_fh.touch(AUTOTB_TVOUT_V);
//N
aesl_fh.touch(AUTOTB_TVIN_N);
aesl_fh.touch(AUTOTB_TVOUT_N);
//rule
aesl_fh.touch(AUTOTB_TVIN_rule);
aesl_fh.touch(AUTOTB_TVOUT_rule);
//EW
aesl_fh.touch(AUTOTB_TVIN_EW);
aesl_fh.touch(AUTOTB_TVOUT_EW);
//NS
aesl_fh.touch(AUTOTB_TVIN_NS);
aesl_fh.touch(AUTOTB_TVOUT_NS);
CodeState = DUMP_INPUTS;
// print E Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_E, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_E);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_E, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.E_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_E, __xlx_sprintf_buffer.data());
}
// print S Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_S, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_S);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_S, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.S_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_S, __xlx_sprintf_buffer.data());
}
// print V Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_V, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_V);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_V, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.V_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_V, __xlx_sprintf_buffer.data());
}
// print N Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_N, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)&__xlx_apatb_param_N);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_N, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.N_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_N, __xlx_sprintf_buffer.data());
}
// print rule Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_rule, __xlx_sprintf_buffer.data());
  {
    sc_bv<32> __xlx_tmp_lv = *((int*)__xlx_apatb_param_rule);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_rule, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.rule_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_rule, __xlx_sprintf_buffer.data());
}
// print EW Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_EW, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_EW);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_EW, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.EW_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_EW, __xlx_sprintf_buffer.data());
}
// print NS Transactions
{
  sprintf(__xlx_sprintf_buffer.data(), "[[transaction]] %d\n", AESL_transaction);
  aesl_fh.write(AUTOTB_TVIN_NS, __xlx_sprintf_buffer.data());
  {
    sc_bv<1> __xlx_tmp_lv = *((char*)__xlx_apatb_param_NS);

    sprintf(__xlx_sprintf_buffer.data(), "%s\n", __xlx_tmp_lv.to_string(SC_HEX).c_str());
    aesl_fh.write(AUTOTB_TVIN_NS, __xlx_sprintf_buffer.data()); 
  }
  tcl_file.set_num(1, &tcl_file.NS_depth);
  sprintf(__xlx_sprintf_buffer.data(), "[[/transaction]] \n");
  aesl_fh.write(AUTOTB_TVIN_NS, __xlx_sprintf_buffer.data());
}
CodeState = CALL_C_DUT;
Tema1Func_hw_stub_wrapper(__xlx_apatb_param_E, __xlx_apatb_param_S, __xlx_apatb_param_V, __xlx_apatb_param_N, __xlx_apatb_param_rule, __xlx_apatb_param_EW, __xlx_apatb_param_NS);
CodeState = DUMP_OUTPUTS;
CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
