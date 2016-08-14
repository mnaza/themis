/*
* Copyright (c) 2015 Cossack Labs Limited
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

#include <soter/soter_container.h>
#include <soter/soter.h>
#include <soter/error.h>
#include <soter/soter_crc32.h>
#include <arpa/inet.h>
#include <string.h>

soter_status_t soter_update_container_checksum(soter_container_hdr_t *hdr)
{
  soter_container_set_crc(hdr, 0);
  soter_container_set_crc(hdr, soter_crc32(hdr, soter_container_size(hdr)));
	return SOTER_SUCCESS;
}

soter_status_t soter_verify_container_checksum(const soter_container_hdr_t *hdr)
{
	uint32_t dummy_crc = 0;
	soter_crc32_t crc = soter_crc32_create();

	soter_crc32_update(&crc, hdr, sizeof(soter_container_hdr_t) - sizeof(uint32_t));
	soter_crc32_update(&crc, &dummy_crc, sizeof(uint32_t));
	soter_crc32_update(&crc, hdr + 1, soter_container_data_size(hdr));
	if (soter_container_crc(hdr) == soter_crc32_final(&crc))
        {
		return SOTER_SUCCESS;
	}
	else
	{
		return SOTER_DATA_CORRUPT;
	}
}

#ifdef STRICT_ALIGNMENT
size_t soter_container_data_size(const soter_container_hdr_t *hdr){
  size_t s_size;						       
  uint8_t* ps_size=(uint8_t*)(&s_size);			       
  uint8_t* phdr_size=(uint8_t*)(&(hdr->_size));
  memcpy(ps_size, phdr_size, 4);
  return ((size_t)ntohl(s_size)) - sizeof(soter_container_hdr_t);
}

size_t soter_container_size(const soter_container_hdr_t *hdr){
  size_t s_size;						       
  uint8_t* ps_size=(uint8_t*)(&s_size);			       
  uint8_t* phdr_size=(uint8_t*)(&(hdr->_size));
  memcpy(ps_size, phdr_size, 4);
  return ((size_t)ntohl(s_size));
}

uint32_t soter_container_crc(const soter_container_hdr_t *hdr){
  uint32_t s_crc;						       
  uint8_t* ps_crc=(uint8_t*)(&s_crc);			       
  uint8_t* phdr_size=(uint8_t*)(&(hdr->_crc));
  memcpy(ps_crc, phdr_size, 4);
  return ((uint32_t)ntohl(s_crc));
}

void soter_container_set_data_size(soter_container_hdr_t *hdr, const uint32_t data_size){
  uint32_t msize=htonl(data_size+sizeof(soter_container_hdr_t));
  const uint8_t *pdata_size = (const uint8_t*)(&msize);
  uint8_t* phdr_size = (uint8_t*)(&(hdr->_size));
  memcpy(phdr_size, pdata_size, 4);  
}

void soter_container_set_size(soter_container_hdr_t *hdr, const uint32_t size){
  uint32_t msize=htonl(size);
  const uint8_t *pdata_size = (const uint8_t*)(&msize);
  uint8_t* phdr_size = (uint8_t*)(&(hdr->_size));
  memcpy(phdr_size, pdata_size, 4);  
}

void soter_container_set_crc(soter_container_hdr_t *hdr, const uint32_t crc){
  uint32_t mcrc=htonl(crc);
  const uint8_t *pcrc = (const uint8_t*)(&mcrc);
  uint8_t* phdr_crc = (uint8_t*)(&(hdr->_crc));
  memcpy(phdr_crc, pcrc, 4);  
}
#endif
