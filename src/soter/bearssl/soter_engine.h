/*
* Copyright (c) 2017 Cossack Labs Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef SOTER_ENGINE_H
#define SOTER_ENGINE_H

#include <soter/soter.h>
#include <sodium.h>
#include "soter_x25519_key.h"
#include "soter_ed25519_key.h"

struct soter_hash_ctx_type
{
  crypto_generichash_state md_ctx;
};

struct soter_sym_ctx_type{
  uint32_t alg;
  union{
    br_block_ctr_class ctr;
  } impl;
};

struct soter_sym_aead_ctx_type{
  uint32_t alg;
  soter_sym_ctx_t cypher;
  br_ghash gcm;
};

struct soter_asym_cipher_type{
  uint32_t alg;
};

struct soter_asym_ka_type{
    soter_x25519_priv_key_t pk;
};

struct soter_sign_ctx_type{
  union{
    soter_ed25519_priv_key_t sk;
    soter_ed25519_pub_key_t pk;
  }key;
  crypto_sign_state state;
};

#endif /* SOTER_ENGINE_H */
