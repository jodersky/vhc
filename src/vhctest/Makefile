#########################################################################
#                         Makefile recursif                             #
#=======================================================================#
# Les variables suivantes sont definis dans un makefile plus haut.      #
# BASEDIR	repertoire de base du projet                                #
# SRCDIR	repertoire contenant le code source                         #
# BINDIR	repertoire ou sont places toutes objets compiles            #
#=======================================================================#
# ==> indique des champs modifiables aisement                           #
#=======================================================================#
# Comme tous les tests dependent du projet principal, les references au #
# dossier `vhc' sont autorisees.                                        #
#########################################################################

# Nom du repertoire contenant ce makefile
LOCALDIR = vhctest

# ==> Rajouter ici les tests a compiler, i.e. les noms des fichiers tests _sans_ extension
# Si un objet X necessite une compilation non-standard (i.e. pas de regle du style X: X.cc X.h), rajouter cet objet
# en fin de BINS ne suffit pas. Il faut de plus creer une nouvelle regle.
BINS = Vector3DTest

# Inclure les headers de vhc (source principale)
CXXFLAGS += -I $(SRCDIR)/vhc/

all: checkdirs $(BINS)

# Verifie l'existance du repertoire de sortie
checkdirs: $(BINDIR)/$(LOCALDIR)

# Cree le repertoire de sortie
$(BINDIR)/$(LOCALDIR):
	@mkdir -p $@

# Regle implicite pour les fichiers sans extension (i.e. pour les executables)
%: %.cc
	$(CXX) $(CXXFLAGS) $< -static -L$(BINDIR)/vhc -lvhc -o $(BINDIR)/$(LOCALDIR)/$@
