#pragma once

class InputManager {
public:
    static void init() {}

    static bool isKeyDown(int key);
    static void getMousePos(double *x, double *y);

    static void update();

private:
    InputManager() {}
};