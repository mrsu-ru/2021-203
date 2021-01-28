CC=g++
CFLAGS=-c -Wall -g
LDFLAGS= -g
SOURCES= \
akishevdv.cpp\
velmiskinnm.cpp\
vecherskymp.cpp\
vidyaykinia.cpp\
gladyshevadn.cpp\
gukovaim.cpp\
dudorovdv.cpp\
zavaryuhinayuv.cpp\
inshakovaas.cpp\
katinda.cpp\
kulaginpa.cpp\
maksimovso.cpp\
nikulovia.cpp\
osipovda.cpp\
parshindi.cpp\
potapkinayuyu.cpp\
rodkinada.cpp\
ruzaevaas.cpp\
svetilnikovdb.cpp\
taynovaa.cpp\
tepaykinma.cpp\
utkinnv.cpp\
chernovaaa.cpp\
shabanovdo.cpp\
zhalninrv.cpp\
lab.cpp\
main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=vvm

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o vvm
