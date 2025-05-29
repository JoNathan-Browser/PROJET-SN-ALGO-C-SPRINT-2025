# Définition du compilateur
CXX = g++

# Options de compilation (utilise C++20)
CXXFLAGS = -Wall -Wextra -std=c++20

# Fichiers source
SRC = main.cpp personnel_administratif.cpp patient.cpp medecin.cpp fichier.cpp
OBJ = $(SRC:.cpp=.o)

# Nom de l'exécutable
EXEC = prog

# Règle principale
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Exécuter le programme
run: $(EXEC)
	./$(EXEC)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	del /F /Q $(OBJ) $(EXEC) 2>nul || exit 0
