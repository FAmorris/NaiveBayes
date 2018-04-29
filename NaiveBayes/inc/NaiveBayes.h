#ifndef __NAIVEBAYES_H
#define __NAIVEBAYES_H

#include "Data.h"

typedef struct{
	i32 *indexPtr;
	i32 count;
	i32 *pPtr;
}PrbDisbTypeDef, *PrbDisbTypeDefPtr;

class NaiveBayes{
public :
	NaiveBayes( i32 r, i32 c, i32 nc, i32 lm = 0 );
	
	void setLanmda( i32 lm );
	void creatFramework();
	void init();
	void probabilityDistribution();
	void setInput( d64 *vPtr );
	void caculateProbability();

	i32 getLanmda() const;
	d64 *getInput() const;
	d64 *getProbability();
	i32 classifyInput() const;

	Data trainData;
	Data testData;
private :
	d64 *inPtr;
	d64 *prbPtr;
	i32 lanmda;
	PrbDisbTypeDefPtr disPtr;
};
#endif  /* __NAIVEBAYES_H */
