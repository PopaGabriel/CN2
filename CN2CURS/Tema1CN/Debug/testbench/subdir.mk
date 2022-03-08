################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tema1Curs_tb.cpp 

OBJS += \
./testbench/tema1Curs_tb.o 

CPP_DEPS += \
./testbench/tema1Curs_tb.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/tema1Curs_tb.o: C:/Users/Catalin/Desktop/CN2CURS/Tema1CN/tema1Curs_tb.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -ID:/Vitis_HLS/2020.2/include -ID:/Vitis_HLS/2020.2/include/ap_sysc -ID:/Vitis_HLS/2020.2/include/etc -ID:/Vitis_HLS/2020.2/win64/tools/auto_cc/include -ID:/Vitis_HLS/2020.2/win64/tools/systemc/include -IC:/Users/Catalin/Desktop/CN2CURS -O0 -g3 -Wall -Wno-unknown-pragmas -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"testbench/tema1Curs_tb.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


