#include "NormalForm.h"
#include <iostream>

ClosureSet* NormalForm::findClosureSet(Relation rel, int closureSize)
{
	return findPermutations(Permutation() , rel, closureSize);
}

ClosureSet* NormalForm::findPermutations(Permutation prefix, Relation rel, int closureSize)
{
	if (closureSize == 0)
	{
		return new ClosureSet(prefix);
	}

	ClosureSet set;
	Relation tmpRel = rel;
	for each (char c in rel.attributes)
	{
		tmpRel = Relation(tmpRel.attributes.substr(1));
		ClosureSet* tmpSet = findPermutations(prefix + Permutation(c), tmpRel, closureSize - 1);
		set += *tmpSet;
		delete tmpSet;
	}

	return new ClosureSet(set);
}