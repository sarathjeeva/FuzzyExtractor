#include <cmath>
#include "thimble/all.h"
#include "minutiae_template.h"

unsigned int MinutiaeTemplate::maxx = DEFAULT_MAX_X;
unsigned int MinutiaeTemplate::maxy = DEFAULT_MAX_Y;

double distance(const Minutia & m1, const Minutia & m2)
{
	double dx = m1.getX()-m2.getX();
	double dy = m1.getY()-m2.getY();
	return std::sqrt(dx*dx+dy*dy);
}

void MinutiaeTemplate::rotate(double degree)
{
	for(int i = 0; i < size; i++)
	{
		int x = minutiae[i].getX();
		int y = minutiae[i].getY();
		minutiae[i].setX(x*cos(degree)-y*sin(degree));
		minutiae[i].setY(x*sin(degree)+y*cos(degree));
	}
}

void MinutiaeTemplate::setReferencePoint()
{
	thimble::Fingerprint fingerprint;
	if(!fingerprint.fromImageFile(filename,500))
	{
		std::cerr << "Failed to read pgm file " << filename << std::endl;
		exit(1);
	}
	thimble::DirectedPoint drp = fingerprint.getDirectedReferencePoint();
	centerx = drp.x;
	centery = drp.y;
	centera = drp.direction.getDirectionAngle();
	std::cerr << filename << ' ' << centerx << ' ' << centery << ' ' << centera << std::endl;
}
