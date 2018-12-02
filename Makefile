CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../imageutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libimage.so ../lib/libmvc.so
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL

OBJS = main.o PhongMaterial.o SceneElement.o ExtendedController.o Block.o Sphere.o Leg.o Bumper.o TableMaterial.o

main: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o main $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libimage.so: ../imageutil/ImageReader.h ../imageutil/ImageReader.c++
	(cd ../imageutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

main.o: main.c++
	$(CPP) $(C_FLAGS) main.c++
PhongMaterial.o: PhongMaterial.c++
	$(CPP) $(C_FLAGS) PhongMaterial.c++
SceneElement.o: SceneElement.c++
	$(CPP) $(C_FLAGS) SceneElement.c++
ExtendedController.o: ExtendedController.c++
	$(CPP) $(C_FLAGS) ExtendedController.c++
Block.o: Block.h Block.c++
	$(CPP) $(C_FLAGS) Block.c++
Sphere.o: Sphere.h Sphere.c++
	$(CPP) $(C_FLAGS) Sphere.c++
Leg.o: Leg.h Leg.c++
	$(CPP) $(C_FLAGS) Leg.c++
Bumper.o: Bumper.h Bumper.c++
	$(CPP) $(C_FLAGS) Bumper.c++
TableMaterial.o: TableMaterial.h TableMaterial.c++
	$(CPP) $(C_FLAGS) TableMaterial.c++

clean:
	rm main *.o

run: main
	./main

again: clean main run
