let addr = DebugSymbol.getFunctionByName("print_loop");
Interceptor.attach(addr, {
    onEnter: function(args) {
        args[0] = ptr(10);
        args[1] = ptr(10);
    },
});
