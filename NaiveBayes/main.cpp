#include <iostream>
#include "./inc/Data.h"
#include "./inc/NaiveBayes.h"
using namespace std;

int main( int agrc, char **argv )
{
	NaiveBayes nb( 2, 15, 2 );
	cin >> nb.trainData;
	cout << "\n����������ݣ�" << endl;
	cin >> nb;
	cout << nb << endl;
}/* end function main */