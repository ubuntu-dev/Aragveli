/*
 * Copyright (c) 2017 Konstantin Tcholokachvili.
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <arch/x86/registers.h>

// Setup interruption service request handling.
void x86_isr_setup(void);

// Interruption service request handler.
void x86_isr_handler(struct registers *r);
