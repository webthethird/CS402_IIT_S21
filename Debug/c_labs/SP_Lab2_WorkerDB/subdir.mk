################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../c_labs/SP_Lab2_WorkerDB/main.c \
../c_labs/SP_Lab2_WorkerDB/readfile.c 

OBJS += \
./c_labs/SP_Lab2_WorkerDB/main.o \
./c_labs/SP_Lab2_WorkerDB/readfile.o 

C_DEPS += \
./c_labs/SP_Lab2_WorkerDB/main.d \
./c_labs/SP_Lab2_WorkerDB/readfile.d 


# Each subdirectory must supply rules for building sources it contributes
c_labs/SP_Lab2_WorkerDB/%.o: ../c_labs/SP_Lab2_WorkerDB/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


