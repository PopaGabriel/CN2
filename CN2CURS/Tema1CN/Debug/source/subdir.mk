################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tema1Curs.cpp 

OBJS += \
./source/tema1Curs.o 

CPP_DEPS += \
./source/tema1Curs.d 


# Each subdirectory must supply rules for building sources it contributes
source/tema1Curs.o: C:/Users/Catalin/Desktop/CN2CURS/Tema1CN/tema1Curs.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -ID:/Vitis_HLS/2020.2/include -ID:/Vitis_HLS/2020.2/include/ap_sysc -ID:/Vitis_HLS/2020.2/include/etc -ID:/Vitis_HLS/2020.2/win64/tools/auto_cc/include -ID:/Vitis_HLS/2020.2/win64/tools/systemc/include -IC:/Users/Catalin/Desktop/CN2CURS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


