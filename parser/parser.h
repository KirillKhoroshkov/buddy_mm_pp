#ifndef BUDDY_MM_PARSER_H
#define BUDDY_MM_PARSER_H

#include <stdbool.h>
#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include "../properties/errors.h"
#include "../properties/messages.h"
#include "../properties/settings.h"
#include <iostream>
#include <sstream>

using namespace std;

Info *parse(string &raw_text);

#endif //BUDDY_MM_PARSER_H
