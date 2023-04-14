#include <SFML/Graphics.hpp>
#include "Ball.h"

double mapValue(double value, double min, double max, double nMin, double nMax)
{
	// Y = (X-A)/(B-A) * (D-C) + C
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

int main(int argc, char **argv)
{
	Ball ball(200, 250, 10, 4000);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 50));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setOutlineColor(sf::Color::Magenta);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(100, 100);

	sf::CircleShape circle;
	circle.setRadius(10);
	circle.setPosition(200, 170);
	circle.setFillColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color::Green);
	circle.setOutlineThickness(2);

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();


		}

		ball.move(ellapsedTime);
		ball.manageCollisionWith(window);

		window.clear();

		//for (int i = 0; i < window.getSize().y; i++)
		//{
			double mappedValue = mapValue(ball.getPosition().x, 0, window.getSize().x, 0, 255);
			double mappedValue2 = mapValue(ball.getPosition().y, 0, window.getSize().y, 0, 255);
			double mappedValue3 = (mappedValue + mappedValue2) / 2.0;
			rdr2.setFillColor(sf::Color(mappedValue, 255 - mappedValue2, mappedValue3));
			
		//}

		rdr2.setPosition(0, 0);
		window.draw(rdr2);

		window.draw(rectangle);
		window.draw(circle);
		ball.draw(window);
		window.display();
	}

	return 0;
}