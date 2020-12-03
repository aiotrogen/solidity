contract C {
    uint constant a = 2;
    bytes2 constant b = 0xabcd;
    bytes3 constant c = "abc";
    bool constant d = true;
    function f() public pure returns (uint w, bytes2 x, bytes3 y, bool z) {
        assembly {
            w := a
            x := b
            y := c
            z := d
        }
    }
}
// ====
// compileToEwasm: also
// compileViaYul: also
// ----
// f() -> 2, left(0xabcd), left(0x616263), true
