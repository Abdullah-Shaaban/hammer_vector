// SPDX-FileCopyrightText: Copyright (c) 2022 by Rivos Inc.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "hammer.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(hammer, m) {
  m.doc() = "Hammer Python Interface";

  pybind11::class_<mem_cfg_t>(m, "mem_cfg_t").def(pybind11::init<reg_t, reg_t>());

  pybind11::class_<mem_t>(m, "mem_t").def(pybind11::init<reg_t>());

  pybind11::class_<Hammer>(m, "Hammer")
      .def(pybind11::init<const char *, const char *, const char *, std::vector<size_t>,
                          std::vector<mem_cfg_t>, const std::string,
                          const std::optional<uint64_t>>())
      .def("hello_world", &Hammer::hello_world)
      .def("get_gpr", &Hammer::get_gpr)
      .def("set_gpr", &Hammer::set_gpr)
      .def("get_fpr", &Hammer::get_fpr)
      .def("get_PC", &Hammer::get_PC)
      .def("set_PC", &Hammer::set_PC)
      .def("get_csr", &Hammer::get_csr)
      .def("get_flen", &Hammer::get_flen)
      .def("get_vlen", &Hammer::get_vlen)
      .def("get_elen", &Hammer::get_elen)
      .def("get_vector_reg", &Hammer::get_vector_reg)
      .def("get_memory_at_VA",
           [](Hammer &h, uint8_t hart_id, uint64_t virtual_address, size_t num_bytes_to_read,
              size_t stride) -> pybind11::object {
             switch (stride) {
               case 1:
                 return pybind11::cast(
                     h.get_memory_at_VA<uint8_t>(hart_id, virtual_address, num_bytes_to_read));
               case 2:
                 return pybind11::cast(
                     h.get_memory_at_VA<uint16_t>(hart_id, virtual_address, num_bytes_to_read));
               case 4:
                 return pybind11::cast(
                     h.get_memory_at_VA<uint32_t>(hart_id, virtual_address, num_bytes_to_read));
               case 8:
                 return pybind11::cast(
                     h.get_memory_at_VA<uint64_t>(hart_id, virtual_address, num_bytes_to_read));
               default:
                 throw std::length_error("Invalid stride");
             }
             return pybind11::none();
           })
      .def("set_memory_at_VA",
           [](Hammer &h, uint8_t hart_id, uint64_t virtual_address, pybind11::list &data,
              size_t stride) {
             switch (stride) {
               case 1:
                 return h.set_memory_at_VA<uint8_t>(hart_id, virtual_address,
                                                    data.cast<std::vector<uint8_t>>());
               case 2:
                 return h.set_memory_at_VA<uint16_t>(hart_id, virtual_address,
                                                     data.cast<std::vector<uint16_t>>());
               case 4:
                 return h.set_memory_at_VA<uint32_t>(hart_id, virtual_address,
                                                     data.cast<std::vector<uint32_t>>());
               case 8:
                 return h.set_memory_at_VA<uint64_t>(hart_id, virtual_address,
                                                     data.cast<std::vector<uint64_t>>());
               default:
                 throw std::length_error("Invalid stride");
             }
             return -EINVAL;
           })
      .def("single_step", &Hammer::single_step);

  // Reference:
  // https://stackoverflow.com/questions/47893832/pybind11-global-level-enum
  pybind11::enum_<PlatformDefines>(m, "PlatformDefines")
      .value("DramBase", DramBase)
      .export_values();

  pybind11::enum_<CsrDefines>(m, "CsrDefines")
      .value("FFLAGS_CSR", FFLAGS_CSR)
      .export_values()
      .value("FRM_CSR", FRM_CSR)
      .export_values()
      .value("FCSR_CSR", FCSR_CSR)
      .export_values()
      .value("VSTART_CSR", VSTART_CSR)
      .export_values()
      .value("VXSAT_CSR", VXSAT_CSR)
      .export_values()
      .value("VXRM_CSR", VXRM_CSR)
      .export_values()
      .value("VCSR_CSR", VCSR_CSR)
      .export_values()
      .value("SEED_CSR", SEED_CSR)
      .export_values()
      .value("CYCLE_CSR", CYCLE_CSR)
      .export_values()
      .value("TIME_CSR", TIME_CSR)
      .export_values()
      .value("INSTRET_CSR", INSTRET_CSR)
      .export_values()
      .value("HPMCOUNTER3_CSR", HPMCOUNTER3_CSR)
      .export_values()
      .value("HPMCOUNTER4_CSR", HPMCOUNTER4_CSR)
      .export_values()
      .value("HPMCOUNTER5_CSR", HPMCOUNTER5_CSR)
      .export_values()
      .value("HPMCOUNTER6_CSR", HPMCOUNTER6_CSR)
      .export_values()
      .value("HPMCOUNTER7_CSR", HPMCOUNTER7_CSR)
      .export_values()
      .value("HPMCOUNTER8_CSR", HPMCOUNTER8_CSR)
      .export_values()
      .value("HPMCOUNTER9_CSR", HPMCOUNTER9_CSR)
      .export_values()
      .value("HPMCOUNTER10_CSR", HPMCOUNTER10_CSR)
      .export_values()
      .value("HPMCOUNTER11_CSR", HPMCOUNTER11_CSR)
      .export_values()
      .value("HPMCOUNTER12_CSR", HPMCOUNTER12_CSR)
      .export_values()
      .value("HPMCOUNTER13_CSR", HPMCOUNTER13_CSR)
      .export_values()
      .value("HPMCOUNTER14_CSR", HPMCOUNTER14_CSR)
      .export_values()
      .value("HPMCOUNTER15_CSR", HPMCOUNTER15_CSR)
      .export_values()
      .value("HPMCOUNTER16_CSR", HPMCOUNTER16_CSR)
      .export_values()
      .value("HPMCOUNTER17_CSR", HPMCOUNTER17_CSR)
      .export_values()
      .value("HPMCOUNTER18_CSR", HPMCOUNTER18_CSR)
      .export_values()
      .value("HPMCOUNTER19_CSR", HPMCOUNTER19_CSR)
      .export_values()
      .value("HPMCOUNTER20_CSR", HPMCOUNTER20_CSR)
      .export_values()
      .value("HPMCOUNTER21_CSR", HPMCOUNTER21_CSR)
      .export_values()
      .value("HPMCOUNTER22_CSR", HPMCOUNTER22_CSR)
      .export_values()
      .value("HPMCOUNTER23_CSR", HPMCOUNTER23_CSR)
      .export_values()
      .value("HPMCOUNTER24_CSR", HPMCOUNTER24_CSR)
      .export_values()
      .value("HPMCOUNTER25_CSR", HPMCOUNTER25_CSR)
      .export_values()
      .value("HPMCOUNTER26_CSR", HPMCOUNTER26_CSR)
      .export_values()
      .value("HPMCOUNTER27_CSR", HPMCOUNTER27_CSR)
      .export_values()
      .value("HPMCOUNTER28_CSR", HPMCOUNTER28_CSR)
      .export_values()
      .value("HPMCOUNTER29_CSR", HPMCOUNTER29_CSR)
      .export_values()
      .value("HPMCOUNTER30_CSR", HPMCOUNTER30_CSR)
      .export_values()
      .value("HPMCOUNTER31_CSR", HPMCOUNTER31_CSR)
      .export_values()
      .value("VL_CSR", VL_CSR)
      .export_values()
      .value("VTYPE_CSR", VTYPE_CSR)
      .export_values()
      .value("VLENB_CSR", VLENB_CSR)
      .export_values()
      .value("SSTATUS_CSR", SSTATUS_CSR)
      .export_values()
      .value("SEDELEG_CSR", SEDELEG_CSR)
      .export_values()
      .value("SIDELEG_CSR", SIDELEG_CSR)
      .export_values()
      .value("SIE_CSR", SIE_CSR)
      .export_values()
      .value("STVEC_CSR", STVEC_CSR)
      .export_values()
      .value("SCOUNTEREN_CSR", SCOUNTEREN_CSR)
      .export_values()
      .value("SENVCFG_CSR", SENVCFG_CSR)
      .export_values()
      .value("SSCRATCH_CSR", SSCRATCH_CSR)
      .export_values()
      .value("SEPC_CSR", SEPC_CSR)
      .export_values()
      .value("SCAUSE_CSR", SCAUSE_CSR)
      .export_values()
      .value("STVAL_CSR", STVAL_CSR)
      .export_values()
      .value("SIP_CSR", SIP_CSR)
      .export_values()
      .value("SATP_CSR", SATP_CSR)
      .export_values()
      .value("SCONTEXT_CSR", SCONTEXT_CSR)
      .export_values()
      .value("VSSTATUS_CSR", VSSTATUS_CSR)
      .export_values()
      .value("VSIE_CSR", VSIE_CSR)
      .export_values()
      .value("VSTVEC_CSR", VSTVEC_CSR)
      .export_values()
      .value("VSSCRATCH_CSR", VSSCRATCH_CSR)
      .export_values()
      .value("VSEPC_CSR", VSEPC_CSR)
      .export_values()
      .value("VSCAUSE_CSR", VSCAUSE_CSR)
      .export_values()
      .value("VSTVAL_CSR", VSTVAL_CSR)
      .export_values()
      .value("VSIP_CSR", VSIP_CSR)
      .export_values()
      .value("VSATP_CSR", VSATP_CSR)
      .export_values()
      .value("HSTATUS_CSR", HSTATUS_CSR)
      .export_values()
      .value("HEDELEG_CSR", HEDELEG_CSR)
      .export_values()
      .value("HIDELEG_CSR", HIDELEG_CSR)
      .export_values()
      .value("HIE_CSR", HIE_CSR)
      .export_values()
      .value("HTIMEDELTA_CSR", HTIMEDELTA_CSR)
      .export_values()
      .value("HCOUNTEREN_CSR", HCOUNTEREN_CSR)
      .export_values()
      .value("HGEIE_CSR", HGEIE_CSR)
      .export_values()
      .value("HENVCFG_CSR", HENVCFG_CSR)
      .export_values()
      .value("HTVAL_CSR", HTVAL_CSR)
      .export_values()
      .value("HIP_CSR", HIP_CSR)
      .export_values()
      .value("HVIP_CSR", HVIP_CSR)
      .export_values()
      .value("HTINST_CSR", HTINST_CSR)
      .export_values()
      .value("HGATP_CSR", HGATP_CSR)
      .export_values()
      .value("HCONTEXT_CSR", HCONTEXT_CSR)
      .export_values()
      .value("HGEIP_CSR", HGEIP_CSR)
      .export_values()
      .value("UTVT_CSR", UTVT_CSR)
      .export_values()
      .value("UNXTI_CSR", UNXTI_CSR)
      .export_values()
      .value("UINTSTATUS_CSR", UINTSTATUS_CSR)
      .export_values()
      .value("USCRATCHCSW_CSR", USCRATCHCSW_CSR)
      .export_values()
      .value("USCRATCHCSWL_CSR", USCRATCHCSWL_CSR)
      .export_values()
      .value("STVT_CSR", STVT_CSR)
      .export_values()
      .value("SNXTI_CSR", SNXTI_CSR)
      .export_values()
      .value("SINTSTATUS_CSR", SINTSTATUS_CSR)
      .export_values()
      .value("SSCRATCHCSW_CSR", SSCRATCHCSW_CSR)
      .export_values()
      .value("SSCRATCHCSWL_CSR", SSCRATCHCSWL_CSR)
      .export_values()
      .value("MTVT_CSR", MTVT_CSR)
      .export_values()
      .value("MNXTI_CSR", MNXTI_CSR)
      .export_values()
      .value("MINTSTATUS_CSR", MINTSTATUS_CSR)
      .export_values()
      .value("MSCRATCHCSW_CSR", MSCRATCHCSW_CSR)
      .export_values()
      .value("MSCRATCHCSWL_CSR", MSCRATCHCSWL_CSR)
      .export_values()
      .value("MSTATUS_CSR", MSTATUS_CSR)
      .export_values()
      .value("MISA_CSR", MISA_CSR)
      .export_values()
      .value("MEDELEG_CSR", MEDELEG_CSR)
      .export_values()
      .value("MIDELEG_CSR", MIDELEG_CSR)
      .export_values()
      .value("MIE_CSR", MIE_CSR)
      .export_values()
      .value("MTVEC_CSR", MTVEC_CSR)
      .export_values()
      .value("MCOUNTEREN_CSR", MCOUNTEREN_CSR)
      .export_values()
      .value("MENVCFG_CSR", MENVCFG_CSR)
      .export_values()
      .value("MCOUNTINHIBIT_CSR", MCOUNTINHIBIT_CSR)
      .export_values()
      .value("MSCRATCH_CSR", MSCRATCH_CSR)
      .export_values()
      .value("MEPC_CSR", MEPC_CSR)
      .export_values()
      .value("MCAUSE_CSR", MCAUSE_CSR)
      .export_values()
      .value("MTVAL_CSR", MTVAL_CSR)
      .export_values()
      .value("MIP_CSR", MIP_CSR)
      .export_values()
      .value("MTINST_CSR", MTINST_CSR)
      .export_values()
      .value("MTVAL2_CSR", MTVAL2_CSR)
      .export_values()
      .value("PMPCFG0_CSR", PMPCFG0_CSR)
      .export_values()
      .value("PMPCFG1_CSR", PMPCFG1_CSR)
      .export_values()
      .value("PMPCFG2_CSR", PMPCFG2_CSR)
      .export_values()
      .value("PMPCFG3_CSR", PMPCFG3_CSR)
      .export_values()
      .value("PMPCFG4_CSR", PMPCFG4_CSR)
      .export_values()
      .value("PMPCFG5_CSR", PMPCFG5_CSR)
      .export_values()
      .value("PMPCFG6_CSR", PMPCFG6_CSR)
      .export_values()
      .value("PMPCFG7_CSR", PMPCFG7_CSR)
      .export_values()
      .value("PMPCFG8_CSR", PMPCFG8_CSR)
      .export_values()
      .value("PMPCFG9_CSR", PMPCFG9_CSR)
      .export_values()
      .value("PMPCFG10_CSR", PMPCFG10_CSR)
      .export_values()
      .value("PMPCFG11_CSR", PMPCFG11_CSR)
      .export_values()
      .value("PMPCFG12_CSR", PMPCFG12_CSR)
      .export_values()
      .value("PMPCFG13_CSR", PMPCFG13_CSR)
      .export_values()
      .value("PMPCFG14_CSR", PMPCFG14_CSR)
      .export_values()
      .value("PMPCFG15_CSR", PMPCFG15_CSR)
      .export_values()
      .value("PMPADDR0_CSR", PMPADDR0_CSR)
      .export_values()
      .value("PMPADDR1_CSR", PMPADDR1_CSR)
      .export_values()
      .value("PMPADDR2_CSR", PMPADDR2_CSR)
      .export_values()
      .value("PMPADDR3_CSR", PMPADDR3_CSR)
      .export_values()
      .value("PMPADDR4_CSR", PMPADDR4_CSR)
      .export_values()
      .value("PMPADDR5_CSR", PMPADDR5_CSR)
      .export_values()
      .value("PMPADDR6_CSR", PMPADDR6_CSR)
      .export_values()
      .value("PMPADDR7_CSR", PMPADDR7_CSR)
      .export_values()
      .value("PMPADDR8_CSR", PMPADDR8_CSR)
      .export_values()
      .value("PMPADDR9_CSR", PMPADDR9_CSR)
      .export_values()
      .value("PMPADDR10_CSR", PMPADDR10_CSR)
      .export_values()
      .value("PMPADDR11_CSR", PMPADDR11_CSR)
      .export_values()
      .value("PMPADDR12_CSR", PMPADDR12_CSR)
      .export_values()
      .value("PMPADDR13_CSR", PMPADDR13_CSR)
      .export_values()
      .value("PMPADDR14_CSR", PMPADDR14_CSR)
      .export_values()
      .value("PMPADDR15_CSR", PMPADDR15_CSR)
      .export_values()
      .value("PMPADDR16_CSR", PMPADDR16_CSR)
      .export_values()
      .value("PMPADDR17_CSR", PMPADDR17_CSR)
      .export_values()
      .value("PMPADDR18_CSR", PMPADDR18_CSR)
      .export_values()
      .value("PMPADDR19_CSR", PMPADDR19_CSR)
      .export_values()
      .value("PMPADDR20_CSR", PMPADDR20_CSR)
      .export_values()
      .value("PMPADDR21_CSR", PMPADDR21_CSR)
      .export_values()
      .value("PMPADDR22_CSR", PMPADDR22_CSR)
      .export_values()
      .value("PMPADDR23_CSR", PMPADDR23_CSR)
      .export_values()
      .value("PMPADDR24_CSR", PMPADDR24_CSR)
      .export_values()
      .value("PMPADDR25_CSR", PMPADDR25_CSR)
      .export_values()
      .value("PMPADDR26_CSR", PMPADDR26_CSR)
      .export_values()
      .value("PMPADDR27_CSR", PMPADDR27_CSR)
      .export_values()
      .value("PMPADDR28_CSR", PMPADDR28_CSR)
      .export_values()
      .value("PMPADDR29_CSR", PMPADDR29_CSR)
      .export_values()
      .value("PMPADDR30_CSR", PMPADDR30_CSR)
      .export_values()
      .value("PMPADDR31_CSR", PMPADDR31_CSR)
      .export_values()
      .value("PMPADDR32_CSR", PMPADDR32_CSR)
      .export_values()
      .value("PMPADDR33_CSR", PMPADDR33_CSR)
      .export_values()
      .value("PMPADDR34_CSR", PMPADDR34_CSR)
      .export_values()
      .value("PMPADDR35_CSR", PMPADDR35_CSR)
      .export_values()
      .value("PMPADDR36_CSR", PMPADDR36_CSR)
      .export_values()
      .value("PMPADDR37_CSR", PMPADDR37_CSR)
      .export_values()
      .value("PMPADDR38_CSR", PMPADDR38_CSR)
      .export_values()
      .value("PMPADDR39_CSR", PMPADDR39_CSR)
      .export_values()
      .value("PMPADDR40_CSR", PMPADDR40_CSR)
      .export_values()
      .value("PMPADDR41_CSR", PMPADDR41_CSR)
      .export_values()
      .value("PMPADDR42_CSR", PMPADDR42_CSR)
      .export_values()
      .value("PMPADDR43_CSR", PMPADDR43_CSR)
      .export_values()
      .value("PMPADDR44_CSR", PMPADDR44_CSR)
      .export_values()
      .value("PMPADDR45_CSR", PMPADDR45_CSR)
      .export_values()
      .value("PMPADDR46_CSR", PMPADDR46_CSR)
      .export_values()
      .value("PMPADDR47_CSR", PMPADDR47_CSR)
      .export_values()
      .value("PMPADDR48_CSR", PMPADDR48_CSR)
      .export_values()
      .value("PMPADDR49_CSR", PMPADDR49_CSR)
      .export_values()
      .value("PMPADDR50_CSR", PMPADDR50_CSR)
      .export_values()
      .value("PMPADDR51_CSR", PMPADDR51_CSR)
      .export_values()
      .value("PMPADDR52_CSR", PMPADDR52_CSR)
      .export_values()
      .value("PMPADDR53_CSR", PMPADDR53_CSR)
      .export_values()
      .value("PMPADDR54_CSR", PMPADDR54_CSR)
      .export_values()
      .value("PMPADDR55_CSR", PMPADDR55_CSR)
      .export_values()
      .value("PMPADDR56_CSR", PMPADDR56_CSR)
      .export_values()
      .value("PMPADDR57_CSR", PMPADDR57_CSR)
      .export_values()
      .value("PMPADDR58_CSR", PMPADDR58_CSR)
      .export_values()
      .value("PMPADDR59_CSR", PMPADDR59_CSR)
      .export_values()
      .value("PMPADDR60_CSR", PMPADDR60_CSR)
      .export_values()
      .value("PMPADDR61_CSR", PMPADDR61_CSR)
      .export_values()
      .value("PMPADDR62_CSR", PMPADDR62_CSR)
      .export_values()
      .value("PMPADDR63_CSR", PMPADDR63_CSR)
      .export_values()
      .value("MSECCFG_CSR", MSECCFG_CSR)
      .export_values()
      .value("TSELECT_CSR", TSELECT_CSR)
      .export_values()
      .value("TDATA1_CSR", TDATA1_CSR)
      .export_values()
      .value("TDATA2_CSR", TDATA2_CSR)
      .export_values()
      .value("TDATA3_CSR", TDATA3_CSR)
      .export_values()
      .value("TINFO_CSR", TINFO_CSR)
      .export_values()
      .value("TCONTROL_CSR", TCONTROL_CSR)
      .export_values()
      .value("MCONTEXT_CSR", MCONTEXT_CSR)
      .export_values()
      .value("MSCONTEXT_CSR", MSCONTEXT_CSR)
      .export_values()
      .value("DCSR_CSR", DCSR_CSR)
      .export_values()
      .value("DPC_CSR", DPC_CSR)
      .export_values()
      .value("DSCRATCH0_CSR", DSCRATCH0_CSR)
      .export_values()
      .value("DSCRATCH1_CSR", DSCRATCH1_CSR)
      .export_values()
      .value("MCYCLE_CSR", MCYCLE_CSR)
      .export_values()
      .value("MINSTRET_CSR", MINSTRET_CSR)
      .export_values()
      .value("MHPMCOUNTER3_CSR", MHPMCOUNTER3_CSR)
      .export_values()
      .value("MHPMCOUNTER4_CSR", MHPMCOUNTER4_CSR)
      .export_values()
      .value("MHPMCOUNTER5_CSR", MHPMCOUNTER5_CSR)
      .export_values()
      .value("MHPMCOUNTER6_CSR", MHPMCOUNTER6_CSR)
      .export_values()
      .value("MHPMCOUNTER7_CSR", MHPMCOUNTER7_CSR)
      .export_values()
      .value("MHPMCOUNTER8_CSR", MHPMCOUNTER8_CSR)
      .export_values()
      .value("MHPMCOUNTER9_CSR", MHPMCOUNTER9_CSR)
      .export_values()
      .value("MHPMCOUNTER10_CSR", MHPMCOUNTER10_CSR)
      .export_values()
      .value("MHPMCOUNTER11_CSR", MHPMCOUNTER11_CSR)
      .export_values()
      .value("MHPMCOUNTER12_CSR", MHPMCOUNTER12_CSR)
      .export_values()
      .value("MHPMCOUNTER13_CSR", MHPMCOUNTER13_CSR)
      .export_values()
      .value("MHPMCOUNTER14_CSR", MHPMCOUNTER14_CSR)
      .export_values()
      .value("MHPMCOUNTER15_CSR", MHPMCOUNTER15_CSR)
      .export_values()
      .value("MHPMCOUNTER16_CSR", MHPMCOUNTER16_CSR)
      .export_values()
      .value("MHPMCOUNTER17_CSR", MHPMCOUNTER17_CSR)
      .export_values()
      .value("MHPMCOUNTER18_CSR", MHPMCOUNTER18_CSR)
      .export_values()
      .value("MHPMCOUNTER19_CSR", MHPMCOUNTER19_CSR)
      .export_values()
      .value("MHPMCOUNTER20_CSR", MHPMCOUNTER20_CSR)
      .export_values()
      .value("MHPMCOUNTER21_CSR", MHPMCOUNTER21_CSR)
      .export_values()
      .value("MHPMCOUNTER22_CSR", MHPMCOUNTER22_CSR)
      .export_values()
      .value("MHPMCOUNTER23_CSR", MHPMCOUNTER23_CSR)
      .export_values()
      .value("MHPMCOUNTER24_CSR", MHPMCOUNTER24_CSR)
      .export_values()
      .value("MHPMCOUNTER25_CSR", MHPMCOUNTER25_CSR)
      .export_values()
      .value("MHPMCOUNTER26_CSR", MHPMCOUNTER26_CSR)
      .export_values()
      .value("MHPMCOUNTER27_CSR", MHPMCOUNTER27_CSR)
      .export_values()
      .value("MHPMCOUNTER28_CSR", MHPMCOUNTER28_CSR)
      .export_values()
      .value("MHPMCOUNTER29_CSR", MHPMCOUNTER29_CSR)
      .export_values()
      .value("MHPMCOUNTER30_CSR", MHPMCOUNTER30_CSR)
      .export_values()
      .value("MHPMCOUNTER31_CSR", MHPMCOUNTER31_CSR)
      .export_values()
      .value("MHPMEVENT3_CSR", MHPMEVENT3_CSR)
      .export_values()
      .value("MHPMEVENT4_CSR", MHPMEVENT4_CSR)
      .export_values()
      .value("MHPMEVENT5_CSR", MHPMEVENT5_CSR)
      .export_values()
      .value("MHPMEVENT6_CSR", MHPMEVENT6_CSR)
      .export_values()
      .value("MHPMEVENT7_CSR", MHPMEVENT7_CSR)
      .export_values()
      .value("MHPMEVENT8_CSR", MHPMEVENT8_CSR)
      .export_values()
      .value("MHPMEVENT9_CSR", MHPMEVENT9_CSR)
      .export_values()
      .value("MHPMEVENT10_CSR", MHPMEVENT10_CSR)
      .export_values()
      .value("MHPMEVENT11_CSR", MHPMEVENT11_CSR)
      .export_values()
      .value("MHPMEVENT12_CSR", MHPMEVENT12_CSR)
      .export_values()
      .value("MHPMEVENT13_CSR", MHPMEVENT13_CSR)
      .export_values()
      .value("MHPMEVENT14_CSR", MHPMEVENT14_CSR)
      .export_values()
      .value("MHPMEVENT15_CSR", MHPMEVENT15_CSR)
      .export_values()
      .value("MHPMEVENT16_CSR", MHPMEVENT16_CSR)
      .export_values()
      .value("MHPMEVENT17_CSR", MHPMEVENT17_CSR)
      .export_values()
      .value("MHPMEVENT18_CSR", MHPMEVENT18_CSR)
      .export_values()
      .value("MHPMEVENT19_CSR", MHPMEVENT19_CSR)
      .export_values()
      .value("MHPMEVENT20_CSR", MHPMEVENT20_CSR)
      .export_values()
      .value("MHPMEVENT21_CSR", MHPMEVENT21_CSR)
      .export_values()
      .value("MHPMEVENT22_CSR", MHPMEVENT22_CSR)
      .export_values()
      .value("MHPMEVENT23_CSR", MHPMEVENT23_CSR)
      .export_values()
      .value("MHPMEVENT24_CSR", MHPMEVENT24_CSR)
      .export_values()
      .value("MHPMEVENT25_CSR", MHPMEVENT25_CSR)
      .export_values()
      .value("MHPMEVENT26_CSR", MHPMEVENT26_CSR)
      .export_values()
      .value("MHPMEVENT27_CSR", MHPMEVENT27_CSR)
      .export_values()
      .value("MHPMEVENT28_CSR", MHPMEVENT28_CSR)
      .export_values()
      .value("MHPMEVENT29_CSR", MHPMEVENT29_CSR)
      .export_values()
      .value("MHPMEVENT30_CSR", MHPMEVENT30_CSR)
      .export_values()
      .value("MHPMEVENT31_CSR", MHPMEVENT31_CSR)
      .export_values()
      .value("MVENDORID_CSR", MVENDORID_CSR)
      .export_values()
      .value("MARCHID_CSR", MARCHID_CSR)
      .export_values()
      .value("MIMPID_CSR", MIMPID_CSR)
      .export_values()
      .value("MHARTID_CSR", MHARTID_CSR)
      .export_values()
      .value("MCONFIGPTR_CSR", MCONFIGPTR_CSR)
      .export_values()
      .value("HTIMEDELTAH_CSR", HTIMEDELTAH_CSR)
      .export_values()
      .value("HENVCFGH_CSR", HENVCFGH_CSR)
      .export_values()
      .value("CYCLEH_CSR", CYCLEH_CSR)
      .export_values()
      .value("TIMEH_CSR", TIMEH_CSR)
      .export_values()
      .value("INSTRETH_CSR", INSTRETH_CSR)
      .export_values()
      .value("HPMCOUNTER3H_CSR", HPMCOUNTER3H_CSR)
      .export_values()
      .value("HPMCOUNTER4H_CSR", HPMCOUNTER4H_CSR)
      .export_values()
      .value("HPMCOUNTER5H_CSR", HPMCOUNTER5H_CSR)
      .export_values()
      .value("HPMCOUNTER6H_CSR", HPMCOUNTER6H_CSR)
      .export_values()
      .value("HPMCOUNTER7H_CSR", HPMCOUNTER7H_CSR)
      .export_values()
      .value("HPMCOUNTER8H_CSR", HPMCOUNTER8H_CSR)
      .export_values()
      .value("HPMCOUNTER9H_CSR", HPMCOUNTER9H_CSR)
      .export_values()
      .value("HPMCOUNTER10H_CSR", HPMCOUNTER10H_CSR)
      .export_values()
      .value("HPMCOUNTER11H_CSR", HPMCOUNTER11H_CSR)
      .export_values()
      .value("HPMCOUNTER12H_CSR", HPMCOUNTER12H_CSR)
      .export_values()
      .value("HPMCOUNTER13H_CSR", HPMCOUNTER13H_CSR)
      .export_values()
      .value("HPMCOUNTER14H_CSR", HPMCOUNTER14H_CSR)
      .export_values()
      .value("HPMCOUNTER15H_CSR", HPMCOUNTER15H_CSR)
      .export_values()
      .value("HPMCOUNTER16H_CSR", HPMCOUNTER16H_CSR)
      .export_values()
      .value("HPMCOUNTER17H_CSR", HPMCOUNTER17H_CSR)
      .export_values()
      .value("HPMCOUNTER18H_CSR", HPMCOUNTER18H_CSR)
      .export_values()
      .value("HPMCOUNTER19H_CSR", HPMCOUNTER19H_CSR)
      .export_values()
      .value("HPMCOUNTER20H_CSR", HPMCOUNTER20H_CSR)
      .export_values()
      .value("HPMCOUNTER21H_CSR", HPMCOUNTER21H_CSR)
      .export_values()
      .value("HPMCOUNTER22H_CSR", HPMCOUNTER22H_CSR)
      .export_values()
      .value("HPMCOUNTER23H_CSR", HPMCOUNTER23H_CSR)
      .export_values()
      .value("HPMCOUNTER24H_CSR", HPMCOUNTER24H_CSR)
      .export_values()
      .value("HPMCOUNTER25H_CSR", HPMCOUNTER25H_CSR)
      .export_values()
      .value("HPMCOUNTER26H_CSR", HPMCOUNTER26H_CSR)
      .export_values()
      .value("HPMCOUNTER27H_CSR", HPMCOUNTER27H_CSR)
      .export_values()
      .value("HPMCOUNTER28H_CSR", HPMCOUNTER28H_CSR)
      .export_values()
      .value("HPMCOUNTER29H_CSR", HPMCOUNTER29H_CSR)
      .export_values()
      .value("HPMCOUNTER30H_CSR", HPMCOUNTER30H_CSR)
      .export_values()
      .value("HPMCOUNTER31H_CSR", HPMCOUNTER31H_CSR)
      .export_values()
      .value("MSTATUSH_CSR", MSTATUSH_CSR)
      .export_values()
      .value("MENVCFGH_CSR", MENVCFGH_CSR)
      .export_values()
      .value("MSECCFGH_CSR", MSECCFGH_CSR)
      .export_values()
      .value("MCYCLEH_CSR", MCYCLEH_CSR)
      .export_values()
      .value("MINSTRETH_CSR", MINSTRETH_CSR)
      .export_values()
      .value("MHPMCOUNTER3H_CSR", MHPMCOUNTER3H_CSR)
      .export_values()
      .value("MHPMCOUNTER4H_CSR", MHPMCOUNTER4H_CSR)
      .export_values()
      .value("MHPMCOUNTER5H_CSR", MHPMCOUNTER5H_CSR)
      .export_values()
      .value("MHPMCOUNTER6H_CSR", MHPMCOUNTER6H_CSR)
      .export_values()
      .value("MHPMCOUNTER7H_CSR", MHPMCOUNTER7H_CSR)
      .export_values()
      .value("MHPMCOUNTER8H_CSR", MHPMCOUNTER8H_CSR)
      .export_values()
      .value("MHPMCOUNTER9H_CSR", MHPMCOUNTER9H_CSR)
      .export_values()
      .value("MHPMCOUNTER10H_CSR", MHPMCOUNTER10H_CSR)
      .export_values()
      .value("MHPMCOUNTER11H_CSR", MHPMCOUNTER11H_CSR)
      .export_values()
      .value("MHPMCOUNTER12H_CSR", MHPMCOUNTER12H_CSR)
      .export_values()
      .value("MHPMCOUNTER13H_CSR", MHPMCOUNTER13H_CSR)
      .export_values()
      .value("MHPMCOUNTER14H_CSR", MHPMCOUNTER14H_CSR)
      .export_values()
      .value("MHPMCOUNTER15H_CSR", MHPMCOUNTER15H_CSR)
      .export_values()
      .value("MHPMCOUNTER16H_CSR", MHPMCOUNTER16H_CSR)
      .export_values()
      .value("MHPMCOUNTER17H_CSR", MHPMCOUNTER17H_CSR)
      .export_values()
      .value("MHPMCOUNTER18H_CSR", MHPMCOUNTER18H_CSR)
      .export_values()
      .value("MHPMCOUNTER19H_CSR", MHPMCOUNTER19H_CSR)
      .export_values()
      .value("MHPMCOUNTER20H_CSR", MHPMCOUNTER20H_CSR)
      .export_values()
      .value("MHPMCOUNTER21H_CSR", MHPMCOUNTER21H_CSR)
      .export_values()
      .value("MHPMCOUNTER22H_CSR", MHPMCOUNTER22H_CSR)
      .export_values()
      .value("MHPMCOUNTER23H_CSR", MHPMCOUNTER23H_CSR)
      .export_values()
      .value("MHPMCOUNTER24H_CSR", MHPMCOUNTER24H_CSR)
      .export_values()
      .value("MHPMCOUNTER25H_CSR", MHPMCOUNTER25H_CSR)
      .export_values()
      .value("MHPMCOUNTER26H_CSR", MHPMCOUNTER26H_CSR)
      .export_values()
      .value("MHPMCOUNTER27H_CSR", MHPMCOUNTER27H_CSR)
      .export_values()
      .value("MHPMCOUNTER28H_CSR", MHPMCOUNTER28H_CSR)
      .export_values()
      .value("MHPMCOUNTER29H_CSR", MHPMCOUNTER29H_CSR)
      .export_values()
      .value("MHPMCOUNTER30H_CSR", MHPMCOUNTER30H_CSR)
      .export_values()
      .value("MHPMCOUNTER31H_CSR", MHPMCOUNTER31H_CSR)
      .export_values();
}
