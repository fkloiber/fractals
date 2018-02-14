#include "assembler.hpp"
#include <asmjit/asmjit.h>

using namespace asmjit;

JitRuntime * RT = nullptr;

#include <cstdio>
/*static void dumpCode(X86Compiler& cb, const char* phase) {
  StringBuilder sb;
  cb.dump(sb);
  printf("%s:\n%s\n", phase, sb.getData());
}*/

#define POS_IN_STRUCT(S, M) ((size_t)(&((S*)0)->M))

static const size_t Offsets[2][10] =
{
    {
        POS_IN_STRUCT(render_info<float>, Pixels),
        POS_IN_STRUCT(render_info<float>, Rows),
        POS_IN_STRUCT(render_info<float>, Cols),
        POS_IN_STRUCT(render_info<float>, RowStride),
        POS_IN_STRUCT(render_info<float>, MaxIter),
        POS_IN_STRUCT(render_info<float>, Bottom),
        POS_IN_STRUCT(render_info<float>, Top),
        POS_IN_STRUCT(render_info<float>, Left),
        POS_IN_STRUCT(render_info<float>, Right),
        POS_IN_STRUCT(render_info<float>, Bailout)
    },
    {
        POS_IN_STRUCT(render_info<double>, Pixels),
        POS_IN_STRUCT(render_info<double>, Rows),
        POS_IN_STRUCT(render_info<double>, Cols),
        POS_IN_STRUCT(render_info<double>, RowStride),
        POS_IN_STRUCT(render_info<double>, MaxIter),
        POS_IN_STRUCT(render_info<double>, Bottom),
        POS_IN_STRUCT(render_info<double>, Top),
        POS_IN_STRUCT(render_info<double>, Left),
        POS_IN_STRUCT(render_info<double>, Right),
        POS_IN_STRUCT(render_info<double>, Bailout)
    }
};

func
Assemble(parse_tree_ptr Tree, int FType)
{
    if (RT == nullptr)
    {
        RT = new JitRuntime;
    }

    static int i = 0;
    char FileName[32];
    sprintf(FileName, "dump%03d.txt", i++);
    FILE * File = fopen(FileName, "w");
    FileLogger Logger(File);

    CodeHolder CH;
    CH.init(RT->getCodeInfo());
    CH.setLogger(&Logger);
    X86Compiler CB(&CH);


    X86Gp Pointer   = x86::rdi;
    X86Gp IntHeight = x86::rax;
    X86Gp IntWidth  = x86::rbx;
    X86Gp Stride    = x86::rcx;
    X86Gp MaxIter   = x86::rdx;

    FuncDetail FD;
    FD.init(FuncSignature1<void, const void*>(CallConv::kIdHost));

    FuncFrameInfo FFI;
    FFI.setDirtyRegs(X86Reg::kKindVec, Utils::mask(0, 1));

    FuncArgsMapper ArgsMap(&FD);
    ArgsMap.assignAll(Pointer);
    ArgsMap.updateFrameInfo(FFI);

    FuncFrameLayout FuncLayout;
    FuncLayout.init(FD, FFI);

    FuncUtils::emitProlog(&CB, FuncLayout);
    FuncUtils::allocArgs(&CB, FuncLayout, ArgsMap);

    CB.mov(IntHeight, x86::ptr(Pointer, Offsets[FType][1]));
    CB.mov(IntWidth,  x86::ptr(Pointer, Offsets[FType][2]));
    CB.mov(Stride,    x86::ptr(Pointer, Offsets[FType][3]));
    //CB.mov(MaxIter,   x86::ptr(Pointer, Offsets[FType][4]));
    /*CB.mov(IntWidth,  x86::ptr(Pointer, Offsets[FType][5]));
    CB.mov(IntWidth,  x86::ptr(Pointer, Offsets[FType][6]));
    CB.mov(IntWidth,  x86::ptr(Pointer, Offsets[FType][7]));
    CB.mov(IntWidth,  x86::ptr(Pointer, Offsets[FType][8]));*/

    FuncUtils::emitEpilog(&CB, FuncLayout);

    //Data256 C = Data256::fromU32(0xdeadbeef);

    //CB.newConst(kConstScopeGlobal, &C, 32);
    CH.sync();

    func FuncPtr;
    Error Err = RT->add(&FuncPtr, &CH);
    printf("%u\n", Err);

    fclose(File);

    return FuncPtr;
}

void
FreeFunc(func F)
{
    if (RT != nullptr)
    {
        RT->release(F);
    }
}
