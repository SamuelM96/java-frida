let addr = Module.enumerateSymbols("example").filter(s => { return s.name == "print_loop" })[0].address;
Interceptor.attach(addr, {
    onEnter: function(args) {
        args[0] = ptr(10);
        args[1] = ptr(10);
    },
});
