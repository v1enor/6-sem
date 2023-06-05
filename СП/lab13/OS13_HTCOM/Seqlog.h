#pragma once
#include <fstream>
extern std::fstream LogCOM(L"CONOUT$", std::fstream::in);
extern LONG Seq{ 0 };
#define SEQ LONG __XXCSeq=InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM<<__XXCSeq<<":"<<(x)<<(y)<<"\n"