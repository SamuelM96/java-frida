Interceptor.attach(DebugSymbol.getFunctionByName("print_loop"), {
    onEnter: function(args) {
        args[0] = ptr(10);
        args[1] = ptr(10);
    },
});
