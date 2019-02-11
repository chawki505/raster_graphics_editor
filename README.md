# Raster graphics editor :
Raster images are stored in a computer in the form of a grid of picture elements, or pixels. 
These pixels contain the image’s color and brightness information. 
Image editors can change the pixels to enhance the image in many ways. 
The pixels can be changed as a group, or individually, by the sophisticated algorithms within the image editors

Le but de ce projet est d’implémenter en langage C un logiciel de manipulation d’images matricielles 
(“raster graphics editor”).

#### Visualisation d’images :
La visualisation des images en cours de traitement se fera à l’aide de la bibliothèque libre SDL 2.0.3 
Cette librairie, minimaliste mais suffisante pour les besoins de ce projet, permet notamment l’ouverture à l’écran 
d’une ou plusieurs fenêtres, le transfert d’images stockées en mémoire vers ces fenêtres, la capture d’événements souris 
et clavier se produisant dans celles-ci, ainsi que la capture des événements sur celles-ci. 
La documentation détaillée de SDL se trouve sur son wiki officiel. 

#### Interface utilisateur :
L’accès aux fonctionnalités du logiciel se fera essentiellement à l’aide d’une interface en ligne de commandes (CLI) 
autrement dit en mode texte depuis un terminal. 
La capture d’événements dans les fenêtres ouvertes par SDL pourra permettre de compléter à la souris certaines demandes d’opérations sur les images affichées 
(e.g. demande de sélection d’une région par commande, suivi d’une sélection effective à la souris).
L'interface doit être suffisamment bien conçue pour autoriser ce type d’entrées de façon fluide et non ambiguë
(opération en cours clairement explicitée, possibilité d’annuler celle-ci lorsqu’elle n’est pas encore complétée,5 etc).

#### Chargement et sauvegarde d’images :
On doit pouvoir à tout moment charger en mémoire une ou plusieurs images, 
transférer une image vers une fenêtre déjà ouverte ou vers une nouvelle fenêtre. 
Les formats d’images supportés doivent être raisonnablement variés : jpg, bmp, png, etc.
Inversement, une image transformée doit pouvoir à tout moment être sauvegardée, sous son format d’origine ou sous un autre format, sous son nom d’origine ou un autre.

#### Sélection de régions :
Toute modification uniforme des pixels d’une image (e.g. remplissage) doit pouvoir s’appliquer soit à l’image toute entière, soit à une région de l’image (rectangulaire, 
délimitée par tracé libre à la souris, regroupant tous les pixels d’une couleur donnée avec ou sans marge de tolérance, etc.)
Le programme doit permettre la sélection de telles régions et mieux encore, l’ajout ou la suppression d’une région à une sélection déjà existante. 
La région en cours de sélection doit être clairement visible à l’écran, et désélectionnable à tout moment.

#### Copier, couper, coller :
Le programme devra permettre de copier ou de couper une région d’image en remplaçant dans ce dernier cas la couleur des pixels coupés par une couleur de fond par défaut 
ou choisie par l’utilisateur. 
Les régions copiées ou coupées doivent pouvoir être collées à des coordonnées quelconques, dans l’image elle-même ou dans une autre image.

#### Transformations :
Le programme doit permettre d’effectuer sur une image les transformations élémentaires suivantes :
1. Symétries verticale et horizontale.
2. Rotation de l’image par un multiple de 90◦.
3. Recadrage de l’image :
    - Par découpage rectangulaire (perte des pixels en dehors du rectangle de recadrage).
    - Par agrandissement de la zone de travail (ajout d’une marge autour des pixels d’origine, colorée en une couleur de fond).
4. Modification de la taille de l’image
5. Les transformations suivantes s’appliqueront à une image ou à la sélection courante :
    - Remplissage par une couleur donnée.
    - Remplacement de couleur, avec ou sans marge de tolérance.
    - Mise en négatif.
    - Mise en niveaux de gris.
    - Mise en noir et blanc.
    - Ajustement de la luminosité et du contraste.


