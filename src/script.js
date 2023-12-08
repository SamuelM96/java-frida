// DebugSymbol isn't working on macOS at this time for some reason, temp work around
var addr;
try {
    // Linux and Windows
    addr = DebugSymbol.getFunctionByName("print_loop");
} catch {
    // macOS
    addr = Module.enumerateSymbols("example").filter(s => { return s.name == "print_loop" })[0].address;
}

if (addr) {

    Interceptor.attach(addr, {
        onEnter: function(args) {
            args[0] = ptr(10);
            args[1] = ptr(10);
        },
    });
} else {
    console.log("Could not find print_loop address.");
}
