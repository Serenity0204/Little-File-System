#include <stdio.h>    
#include <stdlib.h>     
#include <time.h>     
#include "includes/core/engine/engine.h"
using namespace std;


// add main entry
int main()
{
    srand(time(NULL));
    Engine engine;
    engine.run();
}