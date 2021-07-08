# Target and Object Declarations
Target = CrossBufferForLinux
Objects = ../Main.o
Objects += ../CrossBufferLayer/FrameBuffer.o
Objects += ../CrossBufferLayer/MouseSupport.o
Objects += ../CrossBufferLayer/KeyboardSupport.o
Objects += ../CrossBufferLayer/BasicDataTypeDeclarations.o
Objects += ../CrossBufferLayer/FPSCalculator.o
Objects += ../LinuxSimuLayer/SDLHelper.o
Objects += ../LinuxSimuLayer/KeyboardHelper.o
Objects += ../LinuxSimuLayer/CrossBufferForLinux.o

TargetGeneratingArguments = `sdl2-config --libs`
ObjectGeneratingArguments = `sdl2-config --cflags`

Compiler := g++
RMRF := rm -rf

$(Target):$(Objects)
	$(Compiler) $^ -o $@ $(TargetGeneratingArguments)

%.o:%.cpp
	$(Compiler) -c $^ -o $@ $(ObjectGeneratingArguments)

.PHONY:
generateMyself:
	python3 GenerateMakefile.py

clear_o:
	$(RMRF) $(Target) $(Objects)

run_o:
	make
	chmod 777 $(Target)
	./$(Target)

clear:
	make generateMyself
	make clear_o

run:
	make generateMyself
	make run_o

installDependencies:
	sudo apt-get install python3
	sudo apt-get install g++
	sudo apt-get install libsdl2-2.0
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-mixer-dev
	sudo apt-get install libsdl2-image-dev
	sudo apt-get install libsdl2-ttf-dev
	sudo apt-get install libsdl2-gfx-dev
