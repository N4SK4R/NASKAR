stack “grows downwards” from **higher addresses** to **lower addresses**

---

### **push**

Because in x86, a **`push` decrements ESP first, then stores**.

So if `ESP = 0x0012FF80` initially:

```asm
push 5
```

- ESP is decremented by 4 → `ESP = 0x0012FF7C`
- `5` is stored at `[0x0012FF7C]`

---

### **pop**

```asm
pop eax
```

- Reads from `[ESP]` → that’s `[0x0012FF7C]`
- Loads it into `EAX`
- Then increments ESP back to `0x0012FF80`



---

### **EBP**

 At the _start of a function_, `EBP` gets set equal to the **current ESP**
 **EBP = 0x0012FF80** (fixed for this function)
**ESP moves downward** as we `push` stuff (locals, temps, etc.)

---

### **Stack Frame**

Stack Frame is created on top of a function

- The caller pushes the arguments to the function onto the stack, from right to left.
- The caller pushes the return address onto the stack.
- The callee sets up a new stack frame by pushing the old EBP

> _Stack Frame for cdecl_

| From High to Low | Description |
|---------------------|-----|
|...(locals, temps, etc)| Low |
|Old EBP|new ebp points here, after mov ebp, esp|
|Return Address||
|Argument 1 (rightmost)| High|

```
(callee block)
idt_load:

    push ebp             ; save old call frame
    mov ebp, esp         ; initialize new call frame
    
    mov eax, [ebp + 8]   ; access first arg
    lidt [eax]
    
    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret
```

* `ret` pops the return address (the value left by `CALL`) into `EIP`
* After `ret`, the **callee does not clean up arguments** (in cdecl)
* In other conventions (like stdcall), the callee might use `ret n` to clean them up automatically
* `ret 8 `would pop the return address _and_ 2 arguments (8 bytes)
