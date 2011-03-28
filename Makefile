#########################################################################
#                         Makefile principale                           #
#=======================================================================#
# Les variables suivantes sont definis pour des makefiles plus bas.     #
# BASEDIR   repertoire de base du projet                                #
# SRCDIR    repertoire contenant le code source                         #
# BINDIR    repertoire ou sont places toutes objets compiles            #
#########################################################################


# Choix du compilateur
export CXX = g++

# Repertoire de base
export BASEDIR = $(abspath .)

# Repertoire de source
export SRCDIR = $(BASEDIR)/src

# Repertoire de sortie
export BINDIR = $(BASEDIR)/bin

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
# CXXFLAGS += -Wall
# CXXFLAGS += -ansi -pedantic -Wall   # pour les purs et durs
# CXXFLAGS += -g                      # pour debugger
# CXXFLAGS += -pg                     # pour profiler
# LDFLAGS  += -pg                     # pour profiler
# CXXFLAGS += -O2                     # pour optimiser la vitesse

export CXXFLAGS

.PHONY: all checkdirs build test-build doc test clean

all: checkdirs build test-build doc test

# Compile les fichiers source principales
build: checkdirs
	@echo "Building main sources..."
	make all -C $(SRCDIR)/main
	@echo "Done building main sources."

# Compile les tests
test-build: build
	@echo "Building test sources..."
	make all -C $(SRCDIR)/test
	@echo "Done building test sources."

# Genere la documentation
doc:
	@echo "Building doc..."
	doxygen Doxyfile
	@echo "Done building doc."

# Verifie l'existance du repertoire de sortie
checkdirs: $(BINDIR)

# Cree le repertoire de sortie
$(BINDIR):
	@mkdir -p $@

clean:
	rm -rf $(BINDIR)

# Lance les tests
test: test-build
	./testr.sh $(BINDIR)/test

	
