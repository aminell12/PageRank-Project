                  ------README------
Voici notre projet final, concluant le premier semestre en programmation C
de notre deuxième année en licence mathématiques/informatiques à Paris-Dauphine.
Ce projet a pour but de coder l'algorithme du PageRank de GOOGLE de manière plus "simple".


                  ------EXECUTION------
Pour compiler notre programme voici la commande à entrer dans le terminal :

gcc -Wall nomprogramme.c -o nomexecutable

Notre programme possède différents mode :

                  ------ModeTest------

    afin d'exécuter le mode y il suffit d'entrer la commande suivante dans le terminal :

    ./nomexecutable -t k nomfichier.txt f


    '-t' correspond au mode test, 'k' correspond au nombre d'itération du calcul de PageRank
    nomfichier.txt est le fichier contant la matrice à traiter ainsi que les valeurs exactes des PageRank
    et enfin 'f' qui correspond au pourcentage d'erreur qu'on veut atteindre 


                  ------ModeNormal------

    afin d'exécuter le mode y il suffit d'entrer la commande suivante dans le terminal:

    ./nomexecutable -n nomfichier.txt x  k

    '-n' correspond au mode normal, nomfichier.txt est le fichier contenant toutes les pages et ses liens sortant à traiter
    'x' est le nombre de pages les plus importantes à afficher et enfin 'k' correspond au nombre d'itération du calcul de PageRank


ATTENTION : AFIN DE BIEN EXECUTER NOTRE PROGRAMME VEUILLEZ BIEN ENREGISTRER LE FICHIER À TRAITER DANS LE MÊME DOSSIER QUE CE DERNIER
