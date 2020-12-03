contract C {
    uint constant a = 2;
    uint constant aa = a;
    uint constant aaa = aa;
    bytes2 constant b = 0xabcd;
    bytes2 constant bb = b;
    bytes3 constant c = "abc";
    bytes3 constant cc = c;
    bytes3 constant ccc = cc;
    bytes3 constant cccc = ccc;
    bool constant d = true;
    bool constant dd = d;
    function f() public pure returns (uint w, bytes2 x, bytes3 y, bool z) {
        assembly {
            w := aaa
            x := bb
            y := cccc
            z := dd
        }
    }
}
// ====
// compileToEwasm: also
// compileViaYul: also
// ----
// f() -> 2, 0xabcd000000000000000000000000000000000000000000000000000000000000, 0x6162630000000000000000000000000000000000000000000000000000000000, true
