#include <cassert>
#include <cmath>
#include <iostream>

#include "Point.h"
#include "mesFonctions.h"

using namespace std;

// Constructeur SANS paramètres
// x et y à 0, sauf couleur à 7 (light gray)
Point::Point() {
	_x = 0;
	_y = 0;
	_color = COULEUR_DEFAUT;
}

// Constructeur avec 2 paramètres
Point::Point(int x, int y) {
	setX(x);
	setY(y);
	setColor(COULEUR_DEFAUT);
}

// Constructeur de copie
Point::Point(const Point &p) {
	_x = p._x;
	_y = p._y;
	_color = p._color;
}

// destructeur
Point::~Point() {
	_color = _x = _y = 0;
}

// Retourne coord. de x
int Point::getX() const {
	return _x;
}

// Retourne coord. de y
int Point::getY() const {
	return _y;
}

// Retourne couleur (de 0 à 15, 0 étant noir)
int Point::getColor() const {
	return _color;
}

const Point &Point::getPosition() const {
	return *this;
}

// Modifie couleur (de 1 à 15, 0 étant noir)
void Point::setColor(const int color) {
	assert(color >= 0 && color <= 15);
	_color = color;
}

// Modifie coord. de x
void Point::setX(const int x) {
	assert(x >= 0);
	_x = x;
}

// Modifie coord. de y
void Point::setY(const int y) {
	assert(y >= 0);
	_y = y;
}

// Modifie coord. de x et de y
void Point::setPosition(const int x, const int y) {
	setX(x);
	setY(y);
}

// Affiche coord. de x et de y
void Point::print(ostream &sortie) const {
	sortie << "(" << _x << ", " << _y << ")";
}

// Lit coordonnées de x et de y sous le format (x, y)
void Point::read(istream &entree) {
	char skip; // Pour stocker les parenthèses et le virgule ( , )
	entree >> skip >> _x >> skip >> _y >> skip;
}

// Retourne vrai si coordonnées x et y sont égales et faux sinon
bool Point::operator==(const Point &p) const {
	return _x == p._x && _y == p._y;
}

// Retourne vrai si coordonnées x et y sont égales et faux sinon
bool Point::operator!=(const Point &p) const {
	return !(operator==(p));
}

// affecte p dans le Point implicite
const Point &Point::operator=(const Point &p) {
	_x = p._x;
	_y = p._y;
	_color = p._color;

	return *this;
}

// Retourne un Point qui est la somme des 2 autres
Point Point::operator+(const Point &p) const {
	return Point(_x + p._x, _y + p._y);
}

// Retourne un Point qui est la différence des 2 autres
Point Point::operator-(const Point &p) const {
	return Point(_x - p._x, _y - p._y);
}

// Affiche un carré de la couleur et à la position du Point
void Point::draw(ostream &sortie) const {
	setConsoleColor(_color);
	goToXY(_x, _y);
	sortie << BLOCK_CHAR << " ";
	setConsoleColor(COULEUR_DEFAUT);
}

// Retourne de la distance entre 2 Points (milieu)
float distance(const Point &p1, const Point &p2) {
	return sqrt(pow(p1._x - p2._x, 2) + pow(p1._y - p2._y, 2));
}

// Surcharge de l'opérateur d'affichage du Point (cout << p)
ostream &operator<<(ostream &sortie, const Point &p) {
	p.print(sortie);
	return sortie;
}

// Surcharge de l'opérateur de saisie du Point (cin >> p)
istream &operator>>(istream &entree, Point &p) {
	p.read(entree);
	return entree;
}
