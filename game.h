#pragma once


namespace Tmpl8 {

class Surface;
class Oiler;
class Barrier;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	
	// Hi there, Noah here, the following functions were added by me :)
	void OBCollide(Oiler* oiler, Barrier* barrier);
	
	void DrawOiler(Oiler* oiler);
	void DrawBarrier(Barrier* barrier);
private:
	Surface* screen;
};


}; // namespace Tmpl8