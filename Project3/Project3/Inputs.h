#ifndef Inputs_h
#define Inputs_h


class Inputs
{
public:
	Inputs();
	~Inputs();

	int returnDirection();

private:
	bool readInputs();

	enum WASD {empty, W, A, S, D, Q, E, R, T, Y};
	WASD _lastPressedKey = empty;
	bool _inputFlag = false;
};

#endif
