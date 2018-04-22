#include <iostream>
#include "./inc/Data.h"
using namespace std;

int main( int agrc, char **argv )
{
	Data dt( 3, 1, 2 );
	Data dt2( 3, 1, 2 );
	
	cin >> dt >> dt2;
	cout << dt << dt2 << endl;

}/* end function main */