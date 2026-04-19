/***************************************************************************************
 * Auteur      : Geneviève Demers
 ** Nom         : Point.h * Date        : 12 avril 2024 * Description : le Point
 *est représenté par une coordonnée x, y et une couleur.        * Il peut être
 *manipuler et afficher en console soit avec ses coordonnées* ou en étant
 *dessiner à l'aide d'un carré à sa position et à une couleur*
 ****************************************************************************************/

#pragma once

#include <iostream>

class Point {

  protected:
	int _x, _y, // Coordonn�es du Point
		_color; // Couleur du Point en console (0 � 15)
  public:
	Point();			   // Constructeur sans paramètres
	Point(int x, int y);   // Constructeur avec 2 paramètres
	Point(const Point &p); // Constructeur de copie
	~Point();			   // Destructeur

	int getColor() const;			  // Guetteur de couleur
	int getX() const;				  // Guetteur de x
	int getY() const;				  // Guetteur de y
	const Point &getPosition() const; // Guetteur de position

	void setColor(const int color);				// Setteur de couleur
	void setX(const int x);						// Setteur de x
	void setY(const int y);						// Setteur de y
	void setPosition(const int x, const int y); // Setteur de position (x,y)

	void print(std::ostream &sortie) const; // Affiche Point par un flux (cout)
	void read(std::istream &entree);		// Saisit Point par un flux (cin)

	bool operator==(const Point &p) const;	// Retourne vrai si les positions sont égales, faux sinon
	bool operator!=(const Point &p) const;	// Retourne faux si les positions sont égales, vrai sinon
	const Point &operator=(const Point &p); // Affecte la valeur de p dans l'implicite

	Point operator+(const Point &p) const; // Retourne un Point qui est la somme des 2 autres
	Point operator-(const Point &p) const; // Retourne un Point qui est la différence des 2 autres

	void draw(std::ostream &sortie) const;					 // Affiche un carré de la couleur du Point à sa position
	friend float distance(const Point &p1, const Point &p2); // Retourne distance entre 2 Points (milieu)
};
// Surcharge de l'opérateur d'affichage du Point (cout << p)
std::ostream &operator<<(std::ostream &sortie, const Point &p);

// Surcharge de l'opérateur de saisie du Point (cin >> p)
std::istream &operator>>(std::istream &entree, Point &p);
