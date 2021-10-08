#TP_Reseau_1

##Question : Quel protocole choisi-t-on pour le chat du jeu vidéo ? UDP ou TCP et pourquoi ?

Dans le cas d'un chat de jeu vidéo on privilégira l'utilisation du protocole TCP. L'avantage de ce protocole est qu'il est beaucoup
plus fiable que l'UDP. En effet lors d'un envoie de données par un client via TCP vers un serveur, le serveur doit tout d'abord 
accepté la demande du client avant de recevoir les données. Une fois les données reçues le serveur envoie un message au client qui 
confirme la réception des données, chose qui n'existe pas en UDP puisque le serveur se contente de recevoir les données du client
sans lui répondre. Conclusion, TCP permet d'avoir un meilleur suivi sur nos envoi de données.

