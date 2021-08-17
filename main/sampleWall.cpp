//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include "../engine/entities/Tank/Tank.h"
//#include "../gui/constants.h"
//#include "../gui/Loader/Loader.h"
//
//using namespace sf;
//using namespace std;
//
//Loader txt;
//
//sf::Sprite paintTank(Tank& a) {
//	Sprite sprite(txt.load_texture(getPathToTexture("tank", 1)));
//
//	sprite.setOrigin(TANK_CONSTS::WIDTH / 2, TANK_CONSTS::HEIGHT / 2);
//	sprite.setPosition(a.get_cords().x, a.get_cords().y);
//	sprite.setRotation(a.get_angl());
//	sprite.setScale(TANK_CONSTS::BASE::SCALE, TANK_CONSTS::BASE::SCALE);
//
//	return sprite;
//}
//
//float operator* (Vec a, Vec b) {
//	return a.x * b.y - b.x * a.y;
//}
//
//float operator ^ (Vec a, Vec b) {
//	return a.x * b.x + a.y * b.y;
//}
//
//Vec perp(Vec a) {
//	return Vec(-a.y, a.x);
//}
//
//Vec norm(Vec a) {
//	float opr = sqrt(a.x * a.x + a.y * a.y);
//	return Vec(a.x / opr, a.y / opr);
//}
//
//float eps = 1e-8;
//bool eq(float a, float b) {
//	return a == b;
//	//return fabs(a - b) < eps;
//}
//
//struct Segment {
//	Vec begin, end;
//
//	bool is_beetwen(Vec a) {
//		auto b = begin;
//		auto c = end;
//		bool is = 1;
//		is &= eq((c - b) * (a - b), 0);
//		return is & (((b - a) ^ (c - a)) <= 0);
//	}
//};
//
//bool is_cross(Segment a, Segment b) {
//	auto a1 = a.begin, a2 = a.end, b1 = b.begin, b2 = b.end;
//	if (eq((a2 - a1) * (b2 - b1), 0)) {
//		float sc = (a2 - a1) * (b2 - a1);
//		if (!eq(sc, 0)) return 0;
//		bool is = 0;
//		is |= b.is_beetwen(a1);
//		is |= b.is_beetwen(a2);
//		is |= a.is_beetwen(b1);
//		is |= a.is_beetwen(b2);
//		return is;
//	}
//	else {
//		bool is = 1;
//		is &= (((a2 - a1) * (b2 - a1)) * ((a2 - a1) * (b1 - a1)) <= 0);
//		is &= (((b1 - b2) * (a1 - b2)) * ((b1 - b2) * (a2 - b2)) <= 0);
//		return is;
//	}
//}
//
//struct Polygon {
//	std::vector<Vec> points;
//
//	void addPoint(float x, float y) {
//		points.push_back(Vec(x, y));
//	}
//
//	void out() {
//		for (auto i : points) {
//			cout << i.x << " " << i.y << "\n";
//		}
//	}
//};
//
//bool Intersect(Polygon a, Polygon b) {
//	for (int i = 0; i < a.points.size(); ++i) {
//		for (int j = 0; j < b.points.size(); ++j) {
//			int nxi = (i + 1) % a.points.size();
//			int nxj = (j + 1) % b.points.size();
//			if (is_cross(Segment{ a.points[i], a.points[nxi] }, Segment{ b.points[j], b.points[nxj] })) {
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//int main() {
//	RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");
//	Tank tank = Tank(Vec(300, 300), Vec(0, 1), TANK_CONSTS::BASE::SPEED);
//	Tank tank2 = Tank(Vec(100, 100), Vec(0, 1), TANK_CONSTS::BASE::SPEED);
//
//	bool moveForward = false;
//	bool moveRight = false;
//	bool moveLeft = false;
//	bool moveBack = false;
//
//	while (window.isOpen()) {
//		Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == Event::Closed) {
//				window.close();
//			}
//
//			if (event.type == Event::KeyPressed) {
//				if (event.key.code == sf::Keyboard::Right) {
//					moveRight = true;
//				}
//				if (event.key.code == sf::Keyboard::Left) {
//					moveLeft = true;
//				}
//				if (event.key.code == sf::Keyboard::Up) {
//					moveForward = true;
//				}
//				if (event.key.code == sf::Keyboard::Down) {
//					moveBack = true;
//				}
//
//				if (event.key.code == sf::Keyboard::A) {
//
//				}
//			}
//			else if (event.type == Event::KeyReleased) {
//				if (event.key.code == sf::Keyboard::Right) {
//					moveRight = false;
//				}
//				if (event.key.code == sf::Keyboard::Left) {
//					moveLeft = false;
//				}
//				if (event.key.code == sf::Keyboard::Up) {
//					moveForward = false;
//				}
//				if (event.key.code == sf::Keyboard::Down) {
//					moveBack = false;
//				}
//			}
//		}
//
//		if (moveBack) {
//			tank.move(-tank.getSpeed());
//		}
//		if (moveForward) {
//			tank.move(tank.getSpeed());
//		}
//		if (moveLeft) {
//			tank.rotate(-TANK_CONSTS::BASE::ROTATION);
//		}
//		if (moveRight) {
//			tank.rotate(TANK_CONSTS::BASE::ROTATION);
//		}
//
//		auto fig = paintTank(tank);
//		auto cords = tank.get_cords();
//
//		RectangleShape stena(Vec(100, 200));
//		stena.setFillColor(Color(0, 0, 0));
//		stena.move(100, 100);
//		window.clear(Color(255, 255, 255));
//
//		float dx = TANK_CONSTS::WIDTH / 2 * 0.6;
//		float dy = TANK_CONSTS::HEIGHT / 2 * 0.6;
//
//		Polygon tank_polygon;
//		auto cur_point = cords;
//		cur_point += dy * tank.get_dir();
//
//		auto p = norm(perp(tank.get_dir()));
//		cur_point -= p * dx;
//
//		tank_polygon.addPoint(cur_point.x, cur_point.y);
//
//		cur_point += (2 * dx) * p;
//		tank_polygon.addPoint(cur_point.x, cur_point.y);
//
//		cur_point -= (2 * dy) * tank.get_dir();
//
//		tank_polygon.addPoint(cur_point.x, cur_point.y);
//		cur_point -= (2 * dx) * p;
//
//		tank_polygon.addPoint(cur_point.x, cur_point.y);
//
//		Polygon st_polygon;
//		st_polygon.addPoint(100, 100);
//		st_polygon.addPoint(200, 100);
//		st_polygon.addPoint(200, 300);
//		st_polygon.addPoint(100, 300);
//
//		/*cout << "Tank:\n";
//		tank_polygon.out();
//		cout << "\n";
//
//		cout << "Stena:\n";
//		st_polygon.out();
//
//		cout << "\n\n";*/
//
//		/*auto info = stena.getGlobalBounds();
//		std::cout << info.left << " " << info.top << "\n";
//		std::cout << info.width << " " << info.height << "\n";
//		std::cout << "\n\n";
//
//		auto pep = fig.getGlobalBounds();
//		std::cout << pep.left << " " << pep.top << "\n";
//		std::cout << pep.width << " " << pep.height << "\n";
//		*/
//		std::cout << Intersect(st_polygon, tank_polygon) << "\n";
//		if (Intersect(st_polygon, tank_polygon)) {
//			if (moveBack) {
//				tank.move(tank.getSpeed());
//			}
//			if (moveForward) {
//				tank.move(-tank.getSpeed());
//			}
//			if (moveLeft) {
//				tank.rotate(TANK_CONSTS::BASE::ROTATION);
//			}
//			if (moveRight) {
//				tank.rotate(-TANK_CONSTS::BASE::ROTATION);
//			}
//		}
//
//		window.draw(fig);
//		window.draw(stena);
//		window.display();
//	}
//
//
//	return 0;
//}