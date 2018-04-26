#include <iostream>
#include "./inc/Data.h"
#include "./inc/NaiveBayes.h"
using namespace std;

int main( int agrc, char **argv )
{
	NaiveBayes n( 2, 15, 2, 1 );

	cin >> n.trainData;

	n.NB_ProbabilityDistribution();
}/* end function main */