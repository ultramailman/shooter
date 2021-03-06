#ifndef Rect_H
#define Rect_H
#include "Vec2.h"
#include "Size.h"
struct Rect{
	float x, y;
	float w, h;
	
	Rect(float X, float Y, float W, float H) : x(X), y(Y), w(W), h(H)
	{
		if(w < 0)
		{
			x += w;
			w = -w;
		}
		if(h < 0)
		{
			y += h;
			h = -h;
		}
	}
	Rect(Vec2 const & vec, Size const & size): x(vec.x), y(vec.y), w(size.w), h(size.h) {}
	Rect(void): x(0), y(0), w(0), h(0) {}
	Vec2 getCenter(void) const
	{
		Vec2 point;
		point.x = x + w / 2;
		point.y = y + h / 2;
		return point;
	}
	void setCenter(Vec2 const & center)
	{
		x = center.x - w / 2;
		y = center.y - h / 2;
	}
	float getCenterY(void) const
	{
		return y + w / 2;
	}
	void setCenterY(float center_y)
	{
		y = center_y - h / 2;
	}
	Vec2 getPosition(void) const
	{
		return Vec2(x, y);
	}
	float getTop(void) const
	{
		return y;
	}
	float getBottom(void) const
	{
		return y + h;
	}
	float getLeft(void) const
	{
		return x;
	}
	float getRight(void) const
	{
		return x + w;
	}
	bool contains(Vec2 const & p)const
	{
		return p.x >= getLeft() and p.x <= getRight() and p.y >= getTop() and p.y <= getBottom();
	}
	bool disjoint(Rect const & r)const
	{
		return getRight() <= r.getLeft() or
			getLeft() >= r.getRight() or
			getBottom() <= r.getTop() or
			getTop() >= r.getBottom();
	}
	bool intersects(Rect const & r) const
	{
		return not disjoint(r);
	}
};
#endif
