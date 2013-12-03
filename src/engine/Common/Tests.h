//
//  Tests.h
//  Game2
//
//  Created by Stepanov Ilia on 08/11/13.
//  Copyright (c) 2013 Stepanov Ilia. All rights reserved.
//

#ifndef __Game2__Tests__
#define __Game2__Tests__

#include "Obj.h"
#include "ShrPtr.h"

#include <iostream>
#include "Vector2f.h"


void test_vectors();
void test_shr_ptr();

class Test : public Obj
{
	
public:
	Test(int val = 0) : temp(val)
	{
		printf("Test(%i)\n", temp);
	}
	
	~Test()
	{
		printf("~Test() val=%i\n", temp);
	}
	
	int temp;
	long array[1000];
};


#endif /* defined(__Game2__Tests__) */
