#ifndef Rect_H
#define Rect_H
namespace{
struct Rect{
	float x, y;
	float w, h;
	
	Rect(float X, float Y, float W, float H)
	{
		if(W < 0)
		{
			X += W;
			W = -W;
		}
		if(H < 0)
		{
			Y += H;
			H = -H;
		}
		x = X;
		y = Y;
		w = W;
		h = H;
	}
	Rect(void): x(0), y(0), w(0), h(0)
	{
	}
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
		Vec2 point;
		point.x = x;
		point.y = y;
		return point;
	}
	float getTop(void) const
	{
		return y;
	}
	float getBottom(void) const
	{
		return y + w;
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
		return p.x >= x && p.x <= (x + w) &&
			p.y >= y && p.y <= (y + h);
	}
};
}
#endif
