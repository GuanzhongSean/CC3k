#include <iostream>
#include <string>
#include "item.h"

using namespace std;

Item::Item(char Name, string Real_name): Name{Name}, Real_name{Real_name} {}

char Item::getName() {return Name;}

string Item::getReal_name() {return Real_name;};
