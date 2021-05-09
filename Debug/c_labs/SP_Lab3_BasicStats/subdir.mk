################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../c_labs/SP_Lab3_BasicStats/basicstats.c \
../c_labs/SP_Lab3_BasicStats/readfile.c 

OBJS += \
./c_labs/SP_Lab3_BasicStats/basicstats.o \
./c_labs/SP_Lab3_BasicStats/readfile.o 

C_DEPS += \
./c_labs/SP_Lab3_BasicStats/basicstats.d \
./c_labs/SP_Lab3_BasicStats/readfile.d 


# Each subdirectory must supply rules for building sources it contributes
c_labs/SP_Lab3_BasicStats/%.o: ../c_labs/SP_Lab3_BasicStats/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


