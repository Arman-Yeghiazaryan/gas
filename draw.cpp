#include <SFML/Graphics.hpp>
#include "experiment.h"
#include <vector>
#include "Materials.h"
#include "Vector2.h"


Vector2 GetDeltaP(Ball ball1, Ball ball2) {
	Vector2 d;

	d = ball1.position - ball2.position;

	if (d.length() <= ball1.radius + ball2.radius && (ball1.velocity - ball2.velocity) * d <= 0) {
		return (2 * (ball1.velocity - ball2.velocity) / (1 / ball1.mass + 1 / ball2.mass) * d.norm()) * d.norm();
	}
	else
		return Vector2(0, 0);
}

int main() {
	const int HEIGHT = 500, WIDTH = 300;
	int j = 0;
	std::vector<Ball> balls;
	Experiment exp;
	exp.add_wall(Wall_3d(Vector_3d(50, 50, 0), Vector_3d(HEIGHT*3/5, 0, 0), Vector_3d(0, WIDTH*2/3, 0), Vector_3d(0, 0, 0)));
	exp.add_particle(Particle_3d(Vector_3d(HEIGHT/2, WIDTH/2, 0), Vector_3d(100, 100, 0)));
	sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), "Model of ideal gas!!!");
	sf::Clock clock;
	float time, Tbegin = 0;
	sf::RectangleShape rectangle[24];
	for (auto &p : exp.walls){
	
	rectangle[j].setSize(sf::Vector2f(p.a.length(), 0));
	rectangle[j].setOutlineColor(sf::Color::Black);
	rectangle[j].setOutlineThickness(2);
	rectangle[j].setPosition(p.r.x, p.r.y);
	j++;
	
	rectangle[j].setSize(sf::Vector2f(0, p.b.length()));
	rectangle[j].setOutlineColor(sf::Color::Black);
	rectangle[j].setOutlineThickness(2);
	rectangle[j].setPosition(p.r.x, p.r.y);
	j++;

	rectangle[j].setSize(sf::Vector2f(0, p.b.length()));
	rectangle[j].setOutlineColor(sf::Color::Black);
	rectangle[j].setOutlineThickness(2);
	rectangle[j].setPosition(p.r.x + p.a.length(), p.r.y);
	j++;

	rectangle[j].setSize(sf::Vector2f(p.a.length(), 0));
	rectangle[j].setOutlineColor(sf::Color::Black);
	rectangle[j].setOutlineThickness(2);
	rectangle[j].setPosition(p.r.x, p.r.y + p.b.length());
	j++;
	}

	while (window.isOpen())
	{
		sf::Event event;
		sf::Time t = clock.getElapsedTime();
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (balls.size() == 0){
			for (auto &p : exp.p_vector){
				Ball ball;
				ball.position = Vector2(p.r.x, p.r.y);
				ball.radius = 5;
				ball.mass = (rand() % 20 + ball.radius) / 5;
				balls.push_back(ball);
			}
		}
		window.clear(sf::Color::White);

		time = t.asSeconds() - Tbegin;
		Tbegin = t.asSeconds();

		for (auto i = 0; i < balls.size(); ++i) {
			sf::CircleShape ball(balls[i].radius);
			ball.setFillColor(sf::Color::Red);
			ball.setOrigin(balls[i].radius, balls[i].radius);
			ball.setPosition(balls[i].position.x, balls[i].position.y);
			window.draw(ball);
			balls[i].UpdatePosition(time);

			if (balls[i].position.x - balls[i].radius <= 0 || balls[i].position.x + balls[i].radius > HEIGHT) {
				balls[i].velocity.x *= -1;
			}
			if (balls[i].position.y - balls[i].radius <= 0 || balls[i].position.y + balls[i].radius > WIDTH) {
				balls[i].velocity.y *= -1;
			}

			for (auto j = i+1; j < balls.size(); ++j) {
					Vector2 dp;
					dp = GetDeltaP(balls[i], balls[j]);
					balls[j].velocity += dp / balls[j].mass;
					balls[i].velocity += (-1) * dp / balls[i].mass;
			}
		}
		for (auto k = 0; k < j; k++){
			window.draw(rectangle[k]);
		}
		window.display();
	}
	return 0;
}
