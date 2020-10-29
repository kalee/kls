// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 1280;  // 1024;  //640;
const int SCREEN_HEIGHT = 960; // 780; //480;

//const float VELOCITY = .0004f;
//const float VELOCITY = .0002f;
const float VELOCITY = .0003f;

int t = 0;
SDL_Surface* screen;
vector<vec3> stars( 1000 );

// --------------------------------------------------------
// FUNCTION DECLARATIONS
void Draw();
void Update();
void Interpolate( float a, float b, vector<float>& result );
void Interpolate( vec3 a, vec3 b, vector<vec3>& result );

// --------------------------------------------------------
// FUNCTION DEFINITIONS
int main( int argc, char* argv[]) {
	//t = SDL_GetTicks();  // keeps stars from showing.
	for( int s=0; s<stars.size(); ++s ) {
		stars[s].x = 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
		stars[s].y = 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
		stars[s].z = float(rand()) / float(RAND_MAX);
	}
	// min + r * (max - min);
	// ((b - a) * ((float)rand() / RAND_MAX)) + a;
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() ) {
		Update();
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

// --------------------------------------------------------
// void Draw()
void Draw() {
	SDL_FillRect( screen, 0, 0 );
	if( SDL_MUSTLOCK(screen) ) {
		SDL_LockSurface(screen);
	}

	for( size_t s=0; s<stars.size(); ++s ) 	{
		// Add code for projecting and drawing each star
		float f = float( SCREEN_HEIGHT )/2.0f;
		float u = f * (stars[s].x/stars[s].z) + (float( SCREEN_WIDTH ) / 2);
		float v = f * (stars[s].y/stars[s].z) + (float( SCREEN_HEIGHT ) / 2);
		// To make transition smoother, you can fade the brightness of the stars, 
		// letting it depend on the distance to the camera.  Let the brightness be
		// inversely proportional to the squared distance.
		vec3 color = 0.2f * vec3(1,1,1) / (stars[s].z*stars[s].z);
		PutPixelSDL( screen, u, v, color );

	}

	if( SDL_MUSTLOCK(screen) ) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

// --------------------------------------------------------
// void Update()
void Update() {
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
	//cout << VELOCITY << " : " << dt << " : " << VELOCITY * dt << " : .001f\n";
	for( int s=0; s<stars.size(); ++s ) {
		// Add code for update of stars.  Only need to update Z value due to use
		// of pinhole camera at z axis.
		if ( VELOCITY * dt < .00001 ) {
			stars[s].z -= .001f; 
		} else {
			stars[s].z -= VELOCITY * dt; 
		}

		if( stars[s].z <= 0 ) {
			stars[s].z += 1;
		}
		if( stars[s].z > 1 ) {
			stars[s].z -= 1;
		}
	}
}

// --------------------------------------------------------
// void Interpolate( float a, float b, vector<float>& result )
void Interpolate( float a, float b, vector<float>& result ) {
	// vector<float> result
	if (result.size()==1) {
		result[0] = (a+b)/2;
		return;
	}

	float incr = abs(a-b)/(result.size()-1);
	if (a > b) {
		incr *= -1;
	}
	//cout << "incr:" << incr << "\n";
	result[0]=a;
	for (int i=1; i<(result.size());i++) {
		result[i] = result[i-1] + incr;
	}
}


// --------------------------------------------------------
// void Interpolate( vec3 a, vec3 b, vector<vec3>& result )
void Interpolate( vec3 a, vec3 b, vector<vec3>& result ) {
	if (result.size()==0 or (a.x==0 and b.x==0)) {
		return;
	}
	// cout << "Size of result is:" << result.size() << "\n";

	vector<float> x( result.size() );
	Interpolate( a.x, b.x, x );

	vector<float> y( result.size() );
	Interpolate( a.y, b.y, y );

	vector<float> z( result.size() );
	Interpolate( a.z, b.z, z );

	for (int i=0; i < result.size(); i++) {
		result[i].x = x[i];
		result[i].y = y[i];
		result[i].z = z[i];
	}
}

// EOF

