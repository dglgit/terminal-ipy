#define PY_SSZIE_T_CLEAN
#include<Python.h>
#include<stdio.h>

int main(int argc, char *argv[]){
   wchar_t *program =Py_DecodeLocale(argv[0],NULL);
   if (program == NULL){
      fprintf(stderr,"Fatal error, you passed something wrong\n");
      exit(1);
   }
   Py_SetProgramName(program);
   Py_Initialize();
   PyRun_SimpleString("a=43\nprint('num is ',a)");
   PyRun_SimpleString("a+=1\nprint('now a is ',a)");
   PyObject* mainModule=PyImport_AddModule("__main__");
   PyObject* a = PyObject_GetAttrString(mainModule,"a");

   int c_a=PyLong_AsLong(a);
   printf("c_a = %i\n",c_a);
   if(Py_FinalizeEx()>0){
      fprintf(stderr,"finalization error\n");
      exit(120);
   }
   PyMem_RawFree(program);
   return 0;
}
