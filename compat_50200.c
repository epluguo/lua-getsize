#include <lua.h>


#if LUA_VERSION_NUM == 502
#include "compat.h"
#define LUA_CORE
#include "lua5.2/lstate.h"
#include "lua5.2/lobject.h"
#include "lua5.2/lfunc.h"
#include "lua5.2/lstring.h"


void* getArg_50200(lua_State* L, int n) {
  return L->ci->func+n;
}


int getType_50200(void const* v) {
  TValue const* o = v;
  return ttype(o);
}


size_t sizeString_50200(void const* s) {
  TValue const* v = s;
  return sizestring(tsvalue(v));
}


void* tableNode_50200(void const* t) {
  TValue const* h = t;
  return hvalue(h)->node;
}


size_t sizeTable_50200(void const* t, void const* n,
                       unsigned* narr, unsigned* nrec) {
  Table const* h = hvalue((TValue const*)t);
  Node const* dummynode = n;
  *narr = h->sizearray;
  *nrec = (h->node == dummynode ? 0 : sizenode(h));
  return sizeof(Table) + sizeof(TValue) * *narr +
         sizeof(Node) * *nrec;
}


size_t sizeUserdata_50200(void const* u) {
  TValue const* v = u;
  return sizeudata(uvalue(v));
}


size_t sizeThread_50200(void const* v) {
  lua_State const* th = thvalue((TValue const*)v);
  CallInfo* ci = th->base_ci.next;
  size_t cisize = 0;
  for(; ci != NULL; ci = ci->next)
    cisize += sizeof(CallInfo);
  return sizeof(lua_State) + sizeof(TValue) * th->stacksize + cisize;
}

#endif

