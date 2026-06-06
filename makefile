# Laboratorio 4
# Uso: make | make run | make clean

CXX      = g++
# Solo -I.: evita que String.h del lab pise <string.h> del sistema (Windows/MinGW)
CXXFLAGS = -std=c++17 -Wall -I.

TARGET = lab4

SRC = \
	main.cpp \
	Sistema.cpp \
	ISistema.cpp \
	Factory.cpp \
	Usuario.cpp \
	Cliente.cpp \
	Propietario.cpp \
	Inmobiliaria.cpp \
	Inmueble.cpp \
	Casa.cpp \
	Apartamento.cpp \
	Administra.cpp \
	Publicacion.cpp \
	AgendaVisita.cpp

SRC += \
	Datatypes/Direccion.cpp \
	Datatypes/Fecha.cpp \
	Datatypes/DTpropietario.cpp \
	Datatypes/DTPublicacion.cpp \
	Datatypes/DTEspecifica.cpp \
	Datatypes/DTCasa.cpp \
	Datatypes/DTApartamento.cpp \
	Datatypes/DTInmueble.cpp \
	Datatypes/DTInfoInmueble.cpp \
	Datatypes/DTAdministrados.cpp

SRC += \
	ICollection/collections/List.cpp \
	ICollection/collections/ListNode.cpp \
	ICollection/collections/ListIterator.cpp \
	ICollection/collections/OrderedDictionary.cpp \
	ICollection/collections/OrderedDictionaryEntry.cpp \
	ICollection/String.cpp \
	ICollection/Integer.cpp \
	ICollection/interfaces/ICollection.cpp \
	ICollection/interfaces/ICollectible.cpp \
	ICollection/interfaces/IIterator.cpp \
	ICollection/interfaces/IKey.cpp \
	ICollection/interfaces/IDictionary.cpp \
	ICollection/interfaces/OrderedKey.cpp

OBJ = $(SRC:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe
