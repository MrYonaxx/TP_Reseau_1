#TP_Reseau_1

##Question : Quel protocole choisi-t-on pour le chat du jeu vid�o ? UDP ou TCP et pourquoi ?

Dans le cas d'un chat de jeu vid�o on privil�gira l'utilisation du protocole TCP. L'avantage de ce protocole est qu'il est beaucoup
plus fiable que l'UDP. En effet lors d'un envoie de donn�es par un client via TCP vers un serveur, le serveur doit tout d'abord 
accept� la demande du client avant de recevoir les donn�es. Une fois les donn�es re�ues le serveur envoie un message au client qui 
confirme la r�ception des donn�es, chose qui n'existe pas en UDP puisque le serveur se contente de recevoir les donn�es du client
sans lui r�pondre. Conclusion, TCP permet d'avoir un meilleur suivi sur nos envoi de donn�es.

