#include "tank.h"

#include <iostream>


bool Tank::outOfScreen() const
{
    double xmin = GD.SCREEN_WIDTH, xmax = -1, ymin = GD.SCREEN_HEIGHT, ymax = -1;

    for (const auto p : getPolygon())
    {
        xmin = std::min(xmin, p.x);
        xmax = std::max(xmax, p.x);
        ymin = std::min(ymin, p.y);
        ymax = std::max(ymax, p.y);
    }

    return !(0 <= xmin && xmax < GD.SCREEN_WIDTH && 0 <= ymin && ymax < GD.SCREEN_HEIGHT);
}

Tank::Tank()
{
    lastMovement = SDL_GetTicks();
    lastFire = -10000;

    maxTurnSpeed = 144;
    maxSpeed = 100;
    angle = 0.0;
    fireRate = 2.0;

    keys[std::string("up")] = SDLK_UP;
    keys[std::string("down")] = SDLK_DOWN;
    keys[std::string("left")] = SDLK_LEFT;
    keys[std::string("right")] = SDLK_RIGHT;
    keys[std::string("fire")] = SDLK_SPACE;
}

bool Tank::loadImage(const char * fileName)
{
    if (!tankTexture.loadFromFile(fileName))
        return false;

    width = tankTexture.getW();
    height = tankTexture.getH();
}

void Tank::setPos(double x, double y, double _angle)
{
    pos.x = x;
    pos.y = y;
    angle = _angle;

    lastMovement = SDL_GetTicks();
    lastFire = -10000;

    speed = 0;
    turnSpeed = 0;
    shouldFire = false;
}

bool Tank::render() const
{
    return tankTexture.render(pos, angle);
}

void Tank::updatePos()
{
    int time = SDL_GetTicks();
    Point prevPos = pos;
    double prevAngle = angle;

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * PI) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * PI) / 1000.0;

    angle += turnSpeed * (time - lastMovement) / 1000.0;
    if (angle >= 360.0) angle -= 360.0;
    if (angle < 0) angle += 360.0;

    if (outOfScreen()) pos = prevPos, angle = prevAngle;

    lastMovement = time;
}

double Tank::getX() const
{
    return pos.x;
}

double Tank::getY() const
{
    return pos.y;
}

double Tank::getW() const
{
    return height;
}

double Tank::getH() const
{
    return width;
}

double Tank::getAngle() const
{
    return angle;
}

std::vector<Point> Tank::getPolygon() const
{
    Point pivot(pos.x + width / 2, pos.y + height / 2), p;
    std::vector<Point> ret;

    p = pos;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.x += width;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.y += height;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.x += width; p.y += height;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    return ret;
}

void Tank::handleEvent(const SDL_Event &e)
{
    auto sym = e.key.keysym.sym;

    switch (e.type)
    {
        case SDL_KEYDOWN:
            if (sym == keys[std::string("up")]) speed = maxSpeed;
            else if (sym == keys[std::string("down")]) speed = -maxSpeed;
            else if (sym == keys[std::string("left")]) turnSpeed = -maxTurnSpeed;
            else if (sym == keys[std::string("right")]) turnSpeed = maxTurnSpeed;
            else if (sym == keys[std::string("fire")])
            {
                int time = SDL_GetTicks();

                if (time - lastFire > 1000.0 / fireRate)
                {
                    lastFire = time;
                    shouldFire = true;
                }
            }
            else if (sym == SDLK_0)
            {
                for (auto p : getPolygon())
                {
                    std::cout << p.x << ' ' << p.y << '\n';
                }

                std::cout << "\n\n";
            }
            break;
        
        case SDL_KEYUP:
            if (sym == keys[std::string("up")]) { if (speed > 0) speed = 0; }
            else if (sym == keys[std::string("down")]) { if (speed < 0) speed = 0; }
            else if (sym == keys[std::string("left")]) { if (turnSpeed < 0) turnSpeed = 0; }
            else if (sym == keys[std::string("right")]) { if (turnSpeed > 0) turnSpeed = 0; }
            break;
    }
}

Tank::~Tank()
{
    tankTexture.~Texture();
}
