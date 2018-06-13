# All of the sources participating in the build are defined here
-include smc-compute/ops/ops.mk
-include smc-compute/smc-compute.mk

LIBS := -lgmp -lpthread -lcrypto -lssl -ldl

#Add test program to the build variables
CPP_SRCS += innerprod.gen.cpp

OBJS += \


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif


# Add inputs and outputs from these tool invocations to the build variables 
# All Target

innerprod: $(OBJS) $(USER_OBJS) 
	g++ -o secure_server/$@ $@.gen.cpp $(OBJS) $(USER_OBJS) $(LIBS) 
# replace the line above with this one for multi-threaded programs
#	g++ -o test-code test-code.o -I ./ompi/include/ompi $(OBJS) $(USER_OBJS) $(LIBS) -L ./ompi/lib/ompi -L ./ompi/lib/ompi/default -lort -lrt -lboost_thread 

clean:
	-$(RM) *.o secure_server/innerprod

#Clean-Everything
clean-all:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) *.o secure_server/innerprod 

