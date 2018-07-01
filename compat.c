#include <stdlib.h>
#include <lua.h>
#include "compat.h"


extern void* getArg_50103(lua_State*, int);
extern void* getArg_50200(lua_State*, int);
extern void* getArg_50300(lua_State*, int);

static GetArgFunction const getArgFuncs[] = {
#if LUA_VERSION_NUM == 501
  0, 0, 0, getArg_50103, getArg_50103, getArg_50103
#elif LUA_VERSION_NUM == 502
  getArg_50200, getArg_50200, getArg_50200, getArg_50200, getArg_50200
#elif LUA_VERSION_NUM == 503
  getArg_50300, getArg_50300, getArg_50300, getArg_50300, getArg_50300
#else
#error unsupported Lua version
#endif
};



extern size_t sizeString_50103(void const*);
extern size_t sizeString_50200(void const*);
extern size_t sizeString_50300(void const*);
extern size_t sizeString_50301(void const*);

static StringSizeFunction const stringSizeFuncs[] = {
#if LUA_VERSION_NUM == 501
  0, 0, 0, sizeString_50103, sizeString_50103, sizeString_50103
#elif LUA_VERSION_NUM == 502
  sizeString_50200, sizeString_50200, sizeString_50200, sizeString_50200, sizeString_50200
#elif LUA_VERSION_NUM == 503
  sizeString_50300, sizeString_50301, sizeString_50301, sizeString_50301, sizeString_50301
#else
#error unsupported Lua version
#endif
};



extern void* tableNode_50103(void const*);
extern void* tableNode_50200(void const*);
extern void* tableNode_50204(void const*);
extern void* tableNode_50300(void const*);

static TableNodeFunction const tableNodeFuncs[] = {
#if LUA_VERSION_NUM == 501
  0, 0, 0, tableNode_50103, tableNode_50103, tableNode_50103
#elif LUA_VERSION_NUM == 502
  tableNode_50200, tableNode_50200, tableNode_50200, tableNode_50200, tableNode_50204
#elif LUA_VERSION_NUM == 503
  tableNode_50300, tableNode_50300, tableNode_50300, tableNode_50300, tableNode_50300
#else
#error unsupported Lua version
#endif
};



extern size_t sizeTable_50103(void const*, void const*, unsigned*, unsigned*);
extern size_t sizeTable_50200(void const*, void const*, unsigned*, unsigned*);
extern size_t sizeTable_50204(void const*, void const*, unsigned*, unsigned*);
extern size_t sizeTable_50300(void const*, void const*, unsigned*, unsigned*);

static TableSizeFunction const tableSizeFuncs[] = {
#if LUA_VERSION_NUM == 501
  0, 0, 0, sizeTable_50103, sizeTable_50103, sizeTable_50103
#elif LUA_VERSION_NUM == 502
  sizeTable_50200, sizeTable_50200, sizeTable_50200, sizeTable_50200, sizeTable_50204
#elif LUA_VERSION_NUM == 503
  sizeTable_50300, sizeTable_50300, sizeTable_50300, sizeTable_50300, sizeTable_50300
#else
#error unsupported Lua version
#endif
};



extern size_t sizeThread_50103(lua_State const*);
extern size_t sizeThread_50200(lua_State const*);
extern size_t sizeThread_50300(lua_State const*);
extern size_t sizeThread_50302(lua_State const*);

static ThreadSizeFunction const threadSizeFuncs[] = {
#if LUA_VERSION_NUM == 501
  0, 0, 0, sizeThread_50103, sizeThread_50103, sizeThread_50103
#elif LUA_VERSION_NUM == 502
  sizeThread_50200, sizeThread_50200, sizeThread_50200, sizeThread_50200, sizeThread_50200
#elif LUA_VERSION_NUM == 503
  sizeThread_50300, sizeThread_50300, sizeThread_50302, sizeThread_50302, sizeThread_50302
#else
#error unsupported Lua version
#endif
};



GetArgFunction getArg;
StringSizeFunction sizeString;
TableNodeFunction tableNode;
TableSizeFunction sizeTable;
ThreadSizeFunction sizeThread;


static void unsupported(lua_State* L) {
  lua_pushliteral(L, "getsize does not support this Lua (minor) version");
  lua_error(L);
}


void compat_init(lua_State* L) {
  int minor = atoi(LUA_RELEASE+sizeof(LUA_VERSION));
  if (minor < 0)
    unsupported(L);
#define DEFINE_FUNC(_func, _array) \
  do { \
    if ((size_t)minor >= sizeof((_array))/sizeof(*(_array)) || (_array)[minor] == 0) \
      unsupported(L); \
    _func = (_array)[minor]; \
  } while (0)

  DEFINE_FUNC(getArg, getArgFuncs);
  DEFINE_FUNC(sizeString, stringSizeFuncs);
  DEFINE_FUNC(tableNode, tableNodeFuncs);
  DEFINE_FUNC(sizeTable, tableSizeFuncs);
  DEFINE_FUNC(sizeThread, threadSizeFuncs);
#undef DEFINE_FUNC
}

