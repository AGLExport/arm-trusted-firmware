/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Renesas nor the names of its contributors may be
 *     used to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/* SA0 */
/* 0x00000000 */
const unsigned int __attribute__ ((section (".sa0_bootrom"))) bootrom_paramA = 0x00000100;
/* 0x00000080 (Map Type 3 for eMMC Boot)*/
/* 0x000001D4 */
const unsigned int __attribute__ ((section (".sa0_bl2dst_addr3"))) bl2dst_addr3 = 0xE6304000;
/* 0x000002E4 */
const unsigned int __attribute__ ((section (".sa0_bl2dst_size3"))) bl2dst_size3 = 0x0000AA00;
/* 0x00000C00 (Map Type 1 for HyperFlash/QSPI Flash Boot)*/
/* 0x00000D54 */
const unsigned int __attribute__ ((section (".sa0_bl2dst_addr1"))) bl2dst_addr1 = 0xE6304000;
/* 0x00000E64 */
const unsigned int __attribute__ ((section (".sa0_bl2dst_size1"))) bl2dst_size1 = 0x0000AA00;

