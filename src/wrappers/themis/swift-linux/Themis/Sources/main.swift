import CThemis

import CThemis

var res: Int32
var private_key_length: Int = 0
var public_key_length: Int = 0

// private and public keys length determination
res = themis_gen_ec_key_pair(nil, &private_key_length, nil, &public_key_length)
if res != SOTER_BUFFER_TOO_SMALL {
    print("private & public keys length determination error")
    exit(-1)
}

// private and public key memory allocation
var private_key = [UInt8](repeating: 0, count: private_key_length)
var public_key = [UInt8](repeating: 0, count: public_key_length)

// private and public keys generation
res = themis_gen_ec_key_pair(UnsafeMutablePointer(mutating: private_key), &private_key_length, UnsafeMutablePointer(mutating: public_key), &public_key_length)
if res != SOTER_SUCCESS {
    print("private & public keys generation error")
    exit(-1)
}

//result output
print(private_key, private_key_length)
print(private_key, private_key_length)