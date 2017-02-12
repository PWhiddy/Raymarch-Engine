#pragma once
class Controls
{
public:
	bool w, a, s, d, space, lmb, rmb;
	float xRotation, yRotation;
	float lastX, lastY;
	Controls();
	void interpretKey(int keycode, int action);
	void interpretMouseButton(int button, int action);
	void interpretMouseMove(double x, double y);
};