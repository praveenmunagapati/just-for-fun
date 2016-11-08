#include <strings.h>
#include <stdlib.h>

#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/String.h>
#include <String.h>

struct String_c {
  struct Class_c* class;
  char *str;
};

struct StringClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};


static struct StringClass_c string = {NULL, NULL, "String", sizeof(struct StringClass_c)};
static struct StringClass_c stringMeta = {NULL, NULL, "StringMeta", sizeof(struct StringClass_c)};

const Class_t String = &string;
const Class_t StringMeta = &stringMeta;

static char* _toString(String_t this, va_list* list) {
  //TODO: Collect memory
  char *ret = malloc(strlen(this->str)+1);
  strcpy(ret, this->str);
  return ret;
}

static int _equals(String_t this, va_list* list) {
  String_t other = va_arg(*list, String_t);
  if(other == NULL) {
    return false;
  }
  if(this->class != other->class) {
    return false;
  }

  return strcmp(this->str, other->str) == 0;
}

static int _lenght(String_t this, va_list* list) {
  return strlen(this->str);
}


static void _init(String_t this, va_list* list) {
  char *str = va_arg(*list, char*);
  this->str = malloc(strlen(str)+1); //TODO: Collect memory
  strcpy(this->str, str);
}


void loadString(Class_t class) {
  loadObject(class);

  struct StringClass_c *clazz = class;

  clazz->class = StringMeta;
  clazz->superclass = Object;
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[equals] = (Method_t) &_equals;
  clazz->methods[lenght] = (Method_t) &_lenght;
}

void loadStringClass(Class_t class) {
  loadObjectClass(class);
  
  struct StringClass_c *clazz = class;

  clazz->class = StringMeta;
  clazz->superclass = MetaClass;
}

void stringClassLoad() {
  loadString(String);
  loadStringClass(StringMeta);
}
