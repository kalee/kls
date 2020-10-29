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
const float VELOCITY = .0004f;
int t;
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
	t = SDL_GetTicks();
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


//		vec3 color(1,1,1);


/*
void Draw() {
	vec3 topLeft(1,0,0); // red
	vec3 topRight(0,0,1); // blue
	vec3 bottomLeft(0,1,0); // green
	vec3 bottomRight(1,1,0); // yellow

	vector<vec3> leftSide( SCREEN_HEIGHT );
	vector<vec3> rightSide( SCREEN_HEIGHT );
	vector<vec3> widthLayer( SCREEN_WIDTH );
	Interpolate( topLeft, bottomLeft, leftSide );
	Interpolate( topRight, bottomRight, rightSide );


	for( int y=0; y<SCREEN_HEIGHT; ++y ) {
		Interpolate( leftSide[y], rightSide[y], widthLayer);
		for( int x=0; x<SCREEN_WIDTH; ++x ) {
			//vec3 color(0,1,0);
			//PutPixelSDL( screen, x, y, color );
			PutPixelSDL( screen, x, y, widthLayer[x] );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
*/



/*
float r = (float)rand() / (float)RAND_MAX;
return min + r * (max - min);
*/
	/*
	vector<float> result( 10 ); // Create a vector width 10 floats
	//Interpolate( 5, 14, result ); // Fill it with interpolated values
	Interpolate( 14, 5, result ); // Fill it with interpolated values
	for( int i=0; i<result.size(); ++i )
	    cout << result[i] << " "; // Print the result to the terminal
	cout << "\n";
	return 0;
	*/

	/*
	vector<vec3> result(4);
	vec3 a(1,4,9.2);
	vec3 b(4,1,9.8);
	Interpolate(a, b, result);
	for( int i=0; i<result.size(); ++i ) {
		cout << "( "
		<< result[i].x << ", "
		<< result[i].y << ", "
		<< result[i].z << " ) ";
	}
	return 0;
	*/

	// ( 1, 4, 9.2 ) ( 2, 3, 9.4 ) ( 3, 2, 9.6 ) ( 4, 1, 9.8 )

	//vec3 a three-component floating-point vector
	//vec3 zAxis = vec3 (0.0, 0.0, 1.0);

	/*  // Old Bad Code
	if (result.size()==0 or (a==0 and b==0)) {
		return;
	}  // 14 - 5 = 9
	float range = abs(b - a) + 1;  // abs(9.2-9.8) + .1 = .6 
	float incr = range/result.size();  //  incr = abs(9.2-9.8) + 1 
	float start = a;
	if (a > b) {
		incr *= -1;
	}

	result[0] = start;

	for (int i=1; i < result.size(); i++) {
		result[i] = result[i-1] + incr;
	}
	*/



	// vec3 a(1,4,9.2);
	// vec3 b(4,1,9.8);
	// ( 1, 4, 9.2 ) ( 2, 3, 9.4 ) ( 3, 2, 9.6 ) ( 4, 1, 9.8 )  Expected results

		/*
		result[i] = ( x[i], y[i], z[i] );
		cout << "(x[i],y[i],z[i]) = ( "
		<< x[i] << ", "
		<< y[i] << ", "
		<< z[i] << " )\n";
		*/

	/* Output
	Size of result is:4
	incr:1
	incr:-1
	incr:0.2
	(x[i],y[i],z[i]) = ( 1, 4, 9.2 )
	(x[i],y[i],z[i]) = ( 2, 3, 9.4 )
	(x[i],y[i],z[i]) = ( 3, 2, 9.6 )
	(x[i],y[i],z[i]) = ( 4, 1, 9.8 )
	( 0, 0, 0 ) ( 0, 0, 0 ) ( 0, 0, 0 ) ( 0, 0, 0 ) 
	*/

/* Error Error Error

result[i] = (x[i],y[i],z[i]);

klee@lmde ~/software/CgLab1 $ make
[100%] Building CXX object CMakeFiles/FirstLab.dir/skeleton.cpp.o
/home/klee/software/CgLab1/skeleton.cpp: In function ‘void Interpolate(glm::vec3, glm::vec3, std::vector<glm::detail::tvec3<float> >&)’:
/home/klee/software/CgLab1/skeleton.cpp:148:13: error: no match for ‘operator=’ (operand types are ‘glm::detail::tvec3<float>’ and ‘float’)
   result[i] = (x[i],y[i],z[i]);
             ^
/home/klee/software/CgLab1/skeleton.cpp:148:13: note: candidates are:
In file included from /home/klee/software/CgLab1/glm/glm/./core/type_vec3.hpp:341:0,
                 from /home/klee/software/CgLab1/glm/glm/./core/type.hpp:40,
                 from /home/klee/software/CgLab1/glm/glm/glm.hpp:97,
                 from /home/klee/software/CgLab1/skeleton.cpp:13:
/home/klee/software/CgLab1/glm/glm/./core/type_vec3.inl:232:31: note: glm::detail::tvec3<T>& glm::detail::tvec3<T>::operator=(const glm::detail::tvec3<T>&) [with T = float]
  GLM_FUNC_QUALIFIER tvec3<T>& tvec3<T>::operator= 
                               ^
/home/klee/software/CgLab1/glm/glm/./core/type_vec3.inl:232:31: note:   no known conversion for argument 1 from ‘float’ to ‘const glm::detail::tvec3<float>&’
In file included from /home/klee/software/CgLab1/glm/glm/./core/type.hpp:40:0,
                 from /home/klee/software/CgLab1/glm/glm/glm.hpp:97,
                 from /home/klee/software/CgLab1/skeleton.cpp:13:
/home/klee/software/CgLab1/glm/glm/./core/type_vec3.hpp:191:28: note: template<class U> glm::detail::tvec3<T>& glm::detail::tvec3<T>::operator=(const glm::detail::tvec3<U>&) [with U = U; T = float]
   GLM_FUNC_DECL tvec3<T> & operator= (tvec3<U> const & v);
                            ^
/home/klee/software/CgLab1/glm/glm/./core/type_vec3.hpp:191:28: note:   template argument deduction/substitution failed:
/home/klee/software/CgLab1/skeleton.cpp:148:13: note:   mismatched types ‘const glm::detail::tvec3<T>’ and ‘float’
   result[i] = (x[i],y[i],z[i]);
             ^
CMakeFiles/FirstLab.dir/build.make:54: recipe for target 'CMakeFiles/FirstLab.dir/skeleton.cpp.o' failed
make[2]: *** [CMakeFiles/FirstLab.dir/skeleton.cpp.o] Error 1
CMakeFiles/Makefile2:60: recipe for target 'CMakeFiles/FirstLab.dir/all' failed
make[1]: *** [CMakeFiles/FirstLab.dir/all] Error 2
Makefile:76: recipe for target 'all' failed
make: *** [all] Error 2



*/