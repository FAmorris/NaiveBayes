#include <iostream>
#include "./inc/Data.h"
#include "./inc/NaiveBayes.h"
using namespace std;

int main( int agrc, char **argv )
{
	NaiveBayes n( 2, 15, 2, 1 );
	i32 i;

	cin >> n.trainData;
	
	d64 *iPtr = n.getInput();

	cout << "\n输入分类数据：" << endl;

	for( i = 0; i < n.trainData.getMatrixRow(); i++ ){
		cin >> iPtr[ i ];
	}
	n.probabilityDistribution();
	n.caculateProbability();

	d64 *pPtr = n.getProbability();

	for( i = 1; i < n.trainData.getNumOfClasses() + 1; i++ ){
		cout << pPtr[ i ] << " " << endl;
	}
}/* end function main */