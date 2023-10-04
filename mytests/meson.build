# SPDX-FileCopyrightText: 2023 Rivos Inc.
#
# SPDX-License-Identifier: Apache-2.0
test_name = 'vadd_test'
exe = executable(test_name,
                test_name + '.cpp',
                link_with : hammer_lib,
                include_directories : spike_incdirs,
                dependencies : [riscv_libdep]
)

