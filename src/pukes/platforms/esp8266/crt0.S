.section ".header"
.globl __start
_start:
    j _entry

.text
_entry:
    # Clear BSS
    movi a2, __bss_start
    movi a3, __bss_end
    movi a4, 0
.1:
    bgeu a2, a3, .2 # If we reached __bss_end we are done
    s32i a4, a2, 0  # Clear the value
    addi a2, a2, 4  # Move the cursor 4 bytes ahead
    j .1            # Jump back to the beginning

.2:
    # Fetch argc and argv from the stack
    l32i a2, sp, 0 # argc
    l32i a3, sp, 4 # argv
    l32i a4, sp, 8 # env. pointer
    # Stop env. pointer
    movi a5, environ
    s32i a4, a5, 0
    # Now call the __kmain
    movi a0, exit
    j __kmain

.globl environ
.comm envrion, 4 # Create a symbol of 4 bytes size.
