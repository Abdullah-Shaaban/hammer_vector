// SPDX-FileCopyrightText: 2022 Rivos Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include "hammer.h"
#include "cfg.h"
#include <vector>

#define SPIKE_DEBUG_MODE false

int main() {

  const std::string target_binary = "/home/abal/hammer/mytests/vadd";

  std::vector<mem_cfg_t> memory_layout;
  // This is what Spike sets it to
  memory_layout.push_back(mem_cfg_t(reg_t(DRAM_BASE), reg_t(2048) << 20));

  std::vector<size_t> hart_ids{0};

  Hammer hammer = Hammer("RV32IMACV", "MSU", "vlen:64,elen:32", hart_ids, memory_layout, target_binary, std::nullopt);
  std::string isa;
  isa = hammer.get_ISA(0);
  printf("ISA: %s\n", isa.c_str());

  uint32_t vlen = hammer.get_vlen(0);
  if (vlen != 64) {
    printf("Unexpected vlen: %d\n", vlen);
    exit(1);
  }

  uint32_t elen = hammer.get_elen(0);
  if (elen != 32) {
    printf("Unexpected elen: %d\n", elen);
    exit(1);
  }

  uint64_t PC = 0x0;
  uint64_t insn_bits = 0x0;
  uint64_t mask = 0xFFFFFFFF; // Used to discard the garbage leading ones of PC cuz we're using RV32
  while (PC!=0x8000004c)  // Loop until add_vec finishes
  {
    PC = hammer.get_PC(0) & mask;
    insn_bits = hammer.get_insn_bits(0);
    std::string insn_str = hammer.get_insn_str(0);
    printf("PC: 0x%" PRIx64 "\n", PC);
    printf("Instruction bits: 0x%" PRIx64 "\n", insn_bits);
    printf("Disassembled Instruction: %s\n", insn_str.c_str());
    hammer.single_step(0, SPIKE_DEBUG_MODE);
    printf("VL= %lu", hammer.get_csr(0, 0xc20) );
    std::cout << std::endl;
  }
  

  // for (uint32_t i = 0; i < 200; ++i) {
  //   PC = hammer.get_PC(0) & mask;
  //   printf("PC: 0x%" PRIx64 "\n", PC);
  //   uint64_t mstatus = hammer.get_csr(0,0x300);  //a4 = x14
  //   printf("mstatus: 0x%" PRIx64 "\n", mstatus);
  //   hammer.single_step(0);
  // }


  //**************************************
  // Sanity checking of the current setup
  //**************************************
  // std::vector<uint64_t> v0 = hammer.get_vector_reg(0,0); 
  // std::vector<uint64_t> v1 = hammer.get_vector_reg(0,1); 
  // std::vector<uint64_t> v2 = hammer.get_vector_reg(0,2); // The addition result should be in V2
  // for (auto i: v0) {
  //   printf("v0: 0x%" PRIx64 ", ",  i);
  // }
  // std::cout << std::endl;
  // for (auto i: v1) {
  //   printf("v1: 0x%" PRIx64 ", ",  i);
  // }
  // std::cout << std::endl;
  // for (auto i: v2) {
  //   printf("v2: 0x%" PRIx64 ", ",  i);
  // }
  // std::cout << std::endl;
  // if (v0[0]+v1[0] != v2[0]){
  //   printf("Error! Vector Addition Failed\n");
  // }
  // else{
  //   printf("Horaaay! Vector Addition Worked\n");
  // }

}
