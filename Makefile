#########################################################################
#                         Makefile principale                           #
#=======================================================================#
# Les variables suivantes sont definis pour des makefiles plus bas.     #
# BASEDIR	repertoire de base du projet                                #
# SRCDIR	repertoire contenant le code source                         #
# BINDIR	repertoire ou sont places toutes objets compiles            #
#########################################################################


# Choix du compilateur
CXX = g++

# Repertoire de base
export BASEDIR = $(abspath .)

# Repertoire de source
export SRCDIR = $(BASEDIR)/src

# Repertoire de sortie
export BINDIR = $(BASEDIR)/bin

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
# CXXFLAGS += -ansi -pedantic -Wall   # pour les purs et durs
# CXXFLAGS += -g                      # pour debugger
# CXXFLAGS += -pg                     # pour profiler
# LDFLAGS  += -pg                     # pour profiler
# CXXFLAGS += -O2                     # pour optimiser la vitesse

.PHONY: all checkdirs build clean

all: checkdirs build test-build

# Compile les fichiers source principales
build:
	@echo $(BINDIR)
	make all -C $(SRCDIR)/vhc

# Compile les tests
test-build:
	make all -C $(SRCDIR)/vhctest

# Verifie l'existance du repertoire de sortie
checkdirs: $(BINDIR)

# Cree le repertoire de sortie
$(BINDIR):
	@mkdir -p $@

clean:
	@rm -rf $(BINDIR)