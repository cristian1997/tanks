#include "tank.h"

#include <iostream>


bool Tank::setKeys(int _ind, int textInd)
{
    if (_ind < 0 || _ind >= GD.nrMaxTanks) return false;

    ind = _ind;

    keys = nullptr;
    if (!fake) keys = &GD.keys[ind];

    tankTexture = &GD.tankTextures[textInd];

    width = tankTexture->getW();
    height = tankTexture->getH();

    return hpTexture.loadFromText(std::to_string(hp), GD.screenRenderer, GD.font, GD.colors[ind]);
}

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

void Tank::updateSpeed(double newSpeed)
{
    if (speed == 0)
    {
        if (newSpeed < 0)
        {
            applyPowerUp(GD.BEER);
        }
    }
    else if (newSpeed == 0)
    {
        if (speed < 0)
        {
            applyPowerUp(GD.BEER);
        }
    }
    else if (speed * newSpeed < 0)
    {
        applyPowerUp(GD.BEER);
    }

    speed = newSpeed;
}

Tank::Tank(bool _fake)
{
    baseMaxTurnSpeed = maxTurnSpeed = 144;
    baseMaxSpeed = maxSpeed = 100;
    angle = 0.0;
    baseFireRate = fireRate = 2.0;
    dmg = baseDmg;
    fake = _fake;
}

void Tank::initialize(double x, double y, double _angle)
{
    pos.x = prevPos.x = x;
    pos.y = prevPos.y = y;
    angle = prevAngle = _angle;

    lastMovement = SDL_GetTicks();
    lastFire = -10000;

    hp = (fake ? 1 : 10);

    speed = 0;
    turnSpeed = 0;
    shouldFire = false;
    isDestroyed = false;
    isBeer = false;
    onWater = false;

    for (auto i = 0; i < GD.nrPowerUps; ++i)
    {
        lastPowerUp[i] = -1;
    }

    dmg = baseDmg = (GD.gameMode == 2 ? GD.INF : 1);
}

bool Tank::render() const
{
    return tankTexture->render(GD.screenRenderer, pos, angle);
}

bool Tank::renderHp() const
{
    if (fake) return true;

    double xmin = GD.SCREEN_WIDTH, xmax = -1, ymin = GD.SCREEN_HEIGHT, ymax = -1;

    for (const auto p : getPolygon())
    {
        xmin = std::min(xmin, p.x);
        xmax = std::max(xmax, p.x);
        ymin = std::min(ymin, p.y);
        ymax = std::max(ymax, p.y);
    }

    SDL_Rect ret = {xmin, ymin - 20, hpTexture.getW(), hpTexture.getH()};

    return hpTexture.render(GD.screenRenderer, ret);
}

void Tank::applyPhysics()
{
    int time = SDL_GetTicks();
    Point prevPos = pos;
    double prevAngle = angle;

    double speedVal = (onWater ? speed / 2.0 : speed);

    pos.x += speedVal * (time - lastMovement) * cos(angle / 180.0 * PI) / 1000.0;
    pos.y += speedVal * (time - lastMovement) * sin(angle / 180.0 * PI) / 1000.0;

    angle += turnSpeed * (time - lastMovement) / 1000.0;
    if (angle >= 360.0) angle -= 360.0;
    if (angle < 0) angle += 360.0;

    lastMovement = time;
}

void Tank::updatePos()
{
    if (outOfScreen() || !isAllowed)
    {
        pos = prevPos;
        angle = prevAngle;
    }

    prevPos = pos;
    prevAngle = angle;
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

bool Tank::isFake() const
{
    return fake;
}

std::vector<Point> Tank::getPolygon() const
{
    std::vector<Point> ret;

    if (!fake)
    {
        Point pivot(pos.x + width / 2, pos.y + height / 2), p;

        p = pos;
        ret.push_back(Geometry::rotatePoint(p, pivot, angle));

        p = pos; p.x += 33;
        ret.push_back(Geometry::rotatePoint(p, pivot, angle));

        p = pos; p.x += width; p.y += height / 2;
        ret.push_back(Geometry::rotatePoint(p, pivot, angle));

        p = pos; p.x += 33; p.y += height;
        ret.push_back(Geometry::rotatePoint(p, pivot, angle));

        p = pos; p.y += height;
        ret.push_back(Geometry::rotatePoint(p, pivot, angle));
    }
    else
    {
        ret.emplace_back(pos.x, pos.y);
        ret.emplace_back(pos.x + width, pos.y);
        ret.emplace_back(pos.x + width, pos.y + height);
        ret.emplace_back(pos.x, pos.y + height);
    }

    return ret;
}

void Tank::applyPowerUp(GameData::PowerUps type)
{
    switch (type)
    {
        case GameData::HP:
            modifyHp(10);
            break;
        case GameData::FIRE_RATE:
            fireRate = 2 * baseFireRate;
            lastPowerUp[GameData::FIRE_RATE] = SDL_GetTicks() + 5000;
            break;
        case GameData::DMG:
            dmg = (baseDmg == GD.INF ? GD.INF : 2 * baseDmg);
            lastPowerUp[GameData::DMG] = SDL_GetTicks() + 5000;
            break;
        case GameData::SPEED:
            maxSpeed = 2 * baseMaxSpeed;
            lastPowerUp[GameData::SPEED] = SDL_GetTicks() + 5000;

            if (speed != 0) updateSpeed(speed > 0 ? maxSpeed : -maxSpeed);
            break;
        case GameData::BEER:
            std::swap((*keys)[std::string("left")], (*keys)[std::string("right")]);
            isBeer = !isBeer;
            break;
        case GameData::ONE_SHOT:
            dmg = GD.INF;
            break;
        case GameData::REVERSE:
            GD.keys[0].swap(GD.keys[1]);
            break;
        case GameData::BOMB:
            modifyHp(-3);
            break;
    }
}

void Tank::updatePowerUps()
{
    int p, time = SDL_GetTicks();

    p = GameData::PowerUps::FIRE_RATE;
    if (lastPowerUp[p] > 0 && lastPowerUp[p] < time)
    {
        fireRate = baseFireRate;
        lastPowerUp[p] = -1;
    }

    p = GameData::PowerUps::DMG;
    if (lastPowerUp[p] > 0 && lastPowerUp[p] < time && dmg != GD.INF)
    {
        dmg = baseDmg;
        lastPowerUp[p] = -1;
    }

    p = GameData::PowerUps::SPEED;
    if (lastPowerUp[p] > 0 && lastPowerUp[p] < time)
    {
        maxSpeed = baseMaxSpeed;
        lastPowerUp[p] = -1;

        if (speed != 0) updateSpeed(speed > 0 ? maxSpeed : -maxSpeed);
    }
}

void Tank::modifyHp(int diff)
{
    hp += diff;
    if (hp <= 0) isDestroyed = true;
    else
    {
        hpTexture.loadFromText(std::to_string(hp), GD.screenRenderer, GD.font, GD.colors[ind]);
    }
}

int Tank::getDmg()
{
    if (baseDmg == GD.INF) return GD.INF;
    if (dmg == GD.INF) return dmg = baseDmg, GD.INF;
    return dmg;
}

void Tank::handleEvent(const SDL_Event &e)
{
    if (keys == nullptr) return;

    auto sym = e.key.keysym.sym;

    switch (e.type)
    {
        case SDL_KEYDOWN:
            if (sym == (*keys)[std::string("up")]) updateSpeed(maxSpeed);
            else if (sym == (*keys)[std::string("down")]) updateSpeed(-maxSpeed);
            else if (sym == (*keys)[std::string("left")]) turnSpeed = -maxTurnSpeed;
            else if (sym == (*keys)[std::string("right")]) turnSpeed = maxTurnSpeed;
            else if (sym == (*keys)[std::string("fire")])
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
                sym = SDLK_0;
            }
            break;
        
        case SDL_KEYUP:
            if (sym == (*keys)[std::string("up")]) { if (speed > 0) updateSpeed(0); }
            else if (sym == (*keys)[std::string("down")]) { if (speed < 0) updateSpeed(0); }
            else if (sym == (*keys)[std::string("left")]) { if (turnSpeed < 0) turnSpeed = 0; }
            else if (sym == (*keys)[std::string("right")]) { if (turnSpeed > 0) turnSpeed = 0; }
            break;
    }
}
