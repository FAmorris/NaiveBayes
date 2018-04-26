#ifndef __NAIVEBAYES_H
#define __NAIVEBAYES_H

#include "Data.h"

typedef struct{
	i32 *indexPtr;
	i32 count;
	d64 *pPtr;
}PrbDisbTypeDef, *PrbDisbTypeDefPtr;

class NaiveBayes{
public :
	NaiveBayes( i32 r, i32 c, i32 nc, i32 lm = 0 );
	
	void NB_SetLanmda( i32 lm );
	void NB_CreatFramework();
	void NB_Init();
	void NB_ProbabilityDistribution();
	void NB_SetInput( d64 *vPtr );
//	void NB_CaculationProbability();

	i32 NB_GetLanmda() const;
//	i32 NB_ClassifyInput( d64 *vPtr, i32 numOfElement ) const;

	Data trainData;
	Data testData;
private :
	d64 *inPtr;
	d64 *prbPtr;
	i32 lanmda;
	PrbDisbTypeDefPtr disPtr;
};
#endif  /* __NAIVEBAYES_H */
