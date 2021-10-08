#TP_Reseau_1

##Question : Quel protocole choisi-t-on pour le chat du jeu vidéo ? UDP ou TCP et pourquoi ?

Dans le cas d'un chat de jeu vidéo on privilégira l'utilisation du protocole TCP. L'avantage de ce protocole est qu'il est beaucoup
plus fiable que l'UDP. En effet lors d'un envoie de données par un client via TCP vers un serveur, le serveur doit tout d'abord 
accepté la demande du client avant de recevoir les données. Une fois les données reçues le serveur envoie un message au client qui 
confirme la réception des données, chose qui n'existe pas en UDP puisque le serveur se contente de recevoir les données du client
sans lui répondre. Conclusion, TCP permet d'avoir un meilleur suivi sur nos envoi de données.

###Notice d'utilisation 

*Cloner le dépôt github sur Visual Studio et ouvrir le fichier CmakeList.txt présent dans /NetworkLib/ et build le projet pour générer l'exécutable

*Ouvrir un invité de commande 

*Se positionner dans le fichier de l'exécutable qui se trouve dans : "Dossier_du_projet"\NetworkLib\out\build\x64-Debug\ClientServer.exe

*Exécuter la commande suivante : ClientServer.exe -ip "Numero_adresse_ip" -port "Numero_de_port" -protocole "1 pour UDP et 0 pour TCP"