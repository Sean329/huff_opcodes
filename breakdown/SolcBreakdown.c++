// 0x6080604052
348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220d67565680fc150f7bf2c94b8e676ecf23ea079b735f35dfa931010ccd5683acb64736f6c63430008140033


// 3 sections:
// 1. contract creation
// 2. runtime
// 3. metadata

// 1. contract creation code
// Free Memory Pointer 0x6080604052
PUSH1 0x80 // [0x80]
PUSH1 0x40 // [0x40, 0x80]
MSTORE // [] ; memory 0x40 -> 0x80

// If someone sent value with this call, revert!
// Otherwise, jump to the 0x0e PC/JUMPDEST
CALLVALUE // [msg.value]
DUP1 // [msg.value, msg.value]
ISZERO // [msg.value == 0, msg.value]
PUSH1 0x0e // [0x0e, msg.value == 0, msg.value]
JUMPI // [msg.value]
PUSH0 // [0x00, msg.value]
DUP1 // [0x00, 0x00, msg.value]
REVERT // [msg.value]

// Jump dest if msg.value == 0
// sticks the run time code onchain
JUMPDEST // [mag.value]
POP // []
PUSH1 0xa5 // [0xa5]
DUP1 // [0xa5, 0xa5]
PUSH2 0x001b // [0x001b, 0xa5, 0xa5]
PUSH0 // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY // [0xa5] ; memory: [entire runtime code]
PUSH0 // [0x00, 0xa5]
RETURN // [] return the entire runtime code in memory
INVALID // [] End of contrat creation code

// 2. runtime code
// entry point of all calls

// free memory pointer
PUSH1 0x80 // [0x80]
PUSH1 0x40 // [0x40, 0x80]
MSTORE // [] ; memory 0x40 -> 0x80


CALLVALUE // [msg.value]
DUP1 // [msg.value, msg.value]
ISZERO // [msg.value == 0, msg.value]
PUSH1 0x0e // [0x0e, msg.value == 0, msg.value]
JUMPI // [msg.value]
// jump to coninue; or ...

PUSH0 // [0x00, msg.value]
DUP1 // [0x00, 0x00, msg.value]
REVERT // [msg.value]

// if msg.value == 0, start here
// continue!
// check if the calldata is shorter than 4 bytes which is the length of a function selector
JUMPDEST // [msg.value]
POP // []
PUSH1 0x04 // [0x04]
CALLDATASIZE // [msg.data.size, 0x04]
LT // [msg.data.size < 0x04]
PUSH1 0x30 // [0x30, msg.data.size < 0x04]
JUMPI // []
// jump to calldata_jump if the calldata is shorter than 4 bytes which is the length of a function selector

// function dispatcher
PUSH0 // [0x00]
CALLDATALOAD // [first 32 bytes of calldata]
PUSH1 0xe0 // [0xe0, first 32 bytes of calldata]
SHR // [function selector]
DUP1 // [function selector, function selector]
PUSH4 0xcdfead2e // [0xcdfead2e, function selecot, function selecot]
EQ // [function selector == 0xcdfead2e, function selector]
PUSH1 0x34 // [0x34, function selector == 0xcdfead2e, function selector]
JUMPI // [function selector] ; jump to the 0x34 PC/JUMPDEST (set_number_of_horses) if match

DUP1 // [function selector, function selector]
PUSH4 0xe026c017 // [0xe026c017, function selector, function selector]
EQ // [function selector == 0xe026c017, function selector]
PUSH1 0x45 // [0x45, function selector == 0xe026c017, function selector]
JUMPI // [function selector] ; jump to the 0x45 PC/JUMPDEST (read_number_of_horses) if match

// calldata_jump
// revert jumpdest
JUMPDEST // []
PUSH0 // [0x00]
DUP1 // [0x00, 0x00]
REVERT // []


// set horse number jump dest
// pushed some jump dests to the stack for later use
JUMPDEST // [function selector]
PUSH1 0x43 // [0x43, function selector]
PUSH1 0x3f // [0x3f, 0x43, function selector]
CALLDATASIZE // [msg.data.size, 0x3f, 0x43, function selector]
PUSH1 0x04 // [0x04, msg.data.size, 0x3f, 0x43, function selector]
PUSH1 0x59 // [0x59, 0x04, msg.data.size, 0x3f, 0x43, function selector]
JUMP // [0x04, msg.data.size, 0x3f, 0x43, function selector] raw jump to the 0x59 PC/JUMPDEST update number of horses dest2

// update horse number jump dest 4
JUMPDEST // [value_to_update_to, 0x43, function selector]
PUSH0 // [0x00, value_to_update_to, 0x43, function selector]
SSTORE // [0x43, function selector] value is saved to slot 0x00
JUMP // [function selector] raw jump to the 0x43 PC/JUMPDEST update horse number dest5

// update horse number jump dest 5
JUMPDEST // [function selector]
STOP // [function selector]

// read number of horses jump dest
JUMPDEST // [function selector]
PUSH0 // [0x00, function selector]
SLOAD // [value in slot 0x00, function selector]
PUSH1 0x40 // [0x40, value in slot 0x00, function selector]
MLOAD // [0x80, value in slot 0x00, function selector] got 0x80 in the 0x40 free memory pointer
SWAP1 // [value in slot 0x00, 0x80, function selector]
DUP2 // [0x80, value in slot 0x00, 0x80, function selector]
MSTORE // [0x80, function selector] ; memory 0x80 -> value
PUSH1 0x20 // [0x20, 0x80, function selector]
ADD // [0xa0, function selector] 32+128
PUSH1 0x40 // [0x40, 0xa0, function selector]
MLOAD // [0x80, 0xa0, function selector] got 0x80 in the 0x40 free memory pointer
DUP1 // [0x80, 0x80, 0xa0, function selector]
SWAP2 // [0xa0, 0x80, 0x80, function selector]
SUB // 0xa0-0x80 = 0x20, 0x80, function selector]
SWAP1 // [0x80, 0x20, function selector]
RETURN // [function selector] return the value in memory 0x80, of length 0x20 which is 32 bytes


// update horse number jump dest2
// check if the remaining data is more than 32 bytes
JUMPDEST // [0x04, msg.data.size, 0x3f, 0x43, function selector]
PUSH0 // [0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
PUSH1 0x20 // [0x20, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
DUP3 // [0x04, 0x20, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
DUP5 // [msg.data.size, 0x04, 0x20, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
SUB // [msg.data.size - 0x04, 0x20, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
SLT // [msg.data.size - 0x04 < 0x20, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector] ; the remaining has more than 32 bytes?
ISZERO // [bool == 0 ? , 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
PUSH1 0x68 // [0x68, bool == 0 ? , 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
JUMPI // [0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector] jump to the 0x68 PC/JUMPDEST update horse dest3 if remaining data is more than 32 bytes


// revert if there isn't enough calldata
PUSH0 // [0x00, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
DUP1 // [0x00, 0x00, 0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]
REVERT // [0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector]

// update horse number jump dest3
JUMPDEST // [0x00, 0x04, msg.data.size, 0x3f, 0x43, function selector] 
POP // [0x04, msg.data.size, 0x3f, 0x43, function selector]
CALLDATALOAD // [value_to_update_to, msg.data.size, 0x3f, 0x43, function selector]
SWAP2 // [0x3f, msg.data.size, value_to_update_to, 0x43, function selector]
SWAP1 // [msg.data.size, 0x3f, value_to_update_to, 0x43, function selector]
POP // [0x3f, value_to_update_to, 0x43, function selector]
JUMP // [value_to_update_to, 0x43, function selector] raw jump to the 0x3f update horse number dest 4


// 3. metadata
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
SHA3
INVALID
PUSH22 0x65680fc150f7bf2c94b8e676ecf23ea079b735f35dfa
SWAP4
LT
LT
INVALID
INVALID
PUSH9 0x3acb64736f6c634300
ADDMOD
EQ
STOP
CALLER