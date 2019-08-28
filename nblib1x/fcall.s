        program  F.CALL
        def     _f.call
        def     _f.calld
*
* adapter to call fortran functions from "C"
* Portable version
* rev 1.1 7/7/93
*
r0      dequ     0
r1      dequ     1
r2      dequ     2
r3      dequ     3
r4      dequ     4
r5      dequ     5
r6      dequ     6
r7      dequ     7
*
sp      dequ     3
*
off     dequ     8w
args    dequ     off+8w
*
endstk  res     3w
endstp  dataw   endstk
*
        csect
_f.calld cequ    $
        sbr     sp,1            dw call
        bu      beg             merge
_f.call cequ     $
        zbr     sp,1            1w call
beg     cequ     $               common code
        zbr     sp,2            show not ext
        trr     sp,r1           save sp
        sui     sp,off          space for reg save area
        std     r0,2w,sp        save return & old sp
        stf     r4,4w,sp        save reg variables
*
        trr     r1,r7           stack address
        lw      r1,endstp       get sp save address
        stw     sp,0,r1         and save it
        abm     29,endstp       increment stack pointer save addr
*1.1    anmw    r7,=x'00ffffff' if stack is in extended
*1.1    camw    r7,=x'00080000' assume we are running extended
*1.1    blt     skip1           branch if non extended
        trr     r0,r4           save return psd                    1.1
        bl      $+1w            get CC's                           1.1
        xcr     r0,r4           get back return psd                1.1
        tbr     r4,5            see if we are extended             1.1
        bns     skip1           branch if not extended             1.1
        sbm     2,3w,sp         show we were extended
*       cea                     Fortran runs non extended
skip1   cequ     $
        ci      r2,1w           see how many args
        blt     zero            br if none
        stw     r2,args+0w,sp   arg count is 1 or more
        bgt     many            more than 1
        lw      r1,args+1w,sp   arg count is 1, get arg
zero    cequ     $               no args
        trr     r0,r2           return address to reg 2
        la      r0,fret         where to return from Fortran
        lw      r2,0,r2         get function address
        anmw    r2,=x'fffffffe' at least hw address
        cea                     Fortran runs non extended
        bu      0,r2            branch to fortran subroutine
*
many    cequ     $               more than 1 arg
        la      r1,args+1w,sp   args address
        adr     r2,r1           plus arg count
        lw      r2,bu.fret      where to return
        stw     r2,0,r1         store branch to return address
        trr     r0,r2           return address
        la      r0,args,sp      parameter address
        anmw    r0,=x'7ffff'    address is non extended
        lw      r2,0,r2         get function address
        anmw    r2,=x'fffffffe' make at least hw address
        cea                     Fortran runs non extended
        bu      0,r2            branch to Fortran subroutine
*
fret    cequ     $               gets to here on return from Fortran
        lw      r3,endstp       restore stack address
        sui     r3,4            back to start
        stw     r3,endstp       update
        lw      sp,0,r3         restore stack pointer
        zmw     0,r3            clear it, just in case
        trr     r7,r0           get return value
        tbm     1,3w,sp         dw return?
        bns     ret             no, return value
        trr     r6,r0           get dw value
        trr     r7,r1           returned values
ret     cequ     $
        tbm     2,3w,sp         were we extended
        bns     skip2           no, skip ahead
        sea                     restore extended mode
skip2   cequ     $
        lf      r2,2w,sp        restore regs
        bu      1w,r2           back to C code
*
bu.fret bu      fret
        end
