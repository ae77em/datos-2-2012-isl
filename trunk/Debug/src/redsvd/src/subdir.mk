################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/redsvd/src/redsvdFile.cpp \
../src/redsvd/src/util.cpp 

OBJS += \
./src/redsvd/src/redsvdFile.o \
./src/redsvd/src/util.o 

CPP_DEPS += \
./src/redsvd/src/redsvdFile.d \
./src/redsvd/src/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/redsvd/src/%.o: ../src/redsvd/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


