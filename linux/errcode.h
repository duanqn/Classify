#ifndef ERRCODE_H_
#define ERRCODE_H_
namespace duanqn{

  typedef int ERRCODE;
  const int S_OK = 0;
  const int S_FALSE = S_OK + 1;
  const int E_FAIL = S_FALSE + 1;
  const int E_INDEXOVERFLOW = E_FAIL + 1;
  const int E_MEM = E_INDEXOVERFLOW + 1;
  const int E_INVALIDARG = E_MEM + 1;
  const int E_BADFORMAT = E_INVALIDARG + 1;
  const int E_TRIGGER = 0xDEADBEEF;
  const int E_UNEXPECTED = 0x77777777;

}
#endif  // ERRCODE_H_
