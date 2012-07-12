#ifndef _FILTER_BYTECODE_H
#define _FILTER_BYTECODE_H

/*
 * filter-bytecode.h
 *
 * LTTng filter bytecode
 *
 * Copyright 2012 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License, version 2.1 only,
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <lttng/ust-abi.h>

/*
 * offsets are absolute from start of bytecode.
 */

enum filter_register {
	REG_R0 = 0,
	REG_R1 = 1,
	REG_ERROR,
};

enum field_ref_type {
	FIELD_REF_UNKNOWN = 0,
	FIELD_REF_STRING,
	FIELD_REF_SEQUENCE,
	FIELD_REF_S64,
};

struct field_ref {
	/* Initially, symbol offset. After link, field offset. */
	uint16_t offset;
	uint8_t type;	/* enum field_ref_type */
} __attribute__((packed));

struct literal_numeric {
	int64_t v;
} __attribute__((packed));

struct literal_string {
	char string[0];
} __attribute__((packed));

enum filter_op {
	FILTER_OP_UNKNOWN = 0,

	FILTER_OP_RETURN,

	/* binary */
	FILTER_OP_MUL,
	FILTER_OP_DIV,
	FILTER_OP_MOD,
	FILTER_OP_PLUS,
	FILTER_OP_MINUS,
	FILTER_OP_RSHIFT,
	FILTER_OP_LSHIFT,
	FILTER_OP_BIN_AND,
	FILTER_OP_BIN_OR,
	FILTER_OP_BIN_XOR,
	FILTER_OP_EQ,
	FILTER_OP_NE,
	FILTER_OP_GT,
	FILTER_OP_LT,
	FILTER_OP_GE,
	FILTER_OP_LE,

	/* unary */
	FILTER_OP_UNARY_PLUS,
	FILTER_OP_UNARY_MINUS,
	FILTER_OP_UNARY_NOT,

	/* logical */
	FILTER_OP_AND,
	FILTER_OP_OR,

	/* load */
	FILTER_OP_LOAD_FIELD_REF,
	FILTER_OP_LOAD_STRING,
	FILTER_OP_LOAD_S64,

	NR_FILTER_OPS,
};

typedef uint8_t filter_opcode_t;

struct load_op {
	filter_opcode_t op;
	uint8_t reg;		/* enum filter_register */
	char data[0];
	/* data to load. Size known by enum filter_opcode and null-term char. */
} __attribute__((packed));

struct binary_op {
	filter_opcode_t op;
} __attribute__((packed));

struct unary_op {
	filter_opcode_t op;
	uint8_t reg;		/* enum filter_register */
} __attribute__((packed));

/* skip_offset is absolute from start of bytecode */
struct logical_op {
	filter_opcode_t op;
	uint16_t skip_offset;	/* bytecode insn, if skip second test */
} __attribute__((packed));

struct return_op {
	filter_opcode_t op;
} __attribute__((packed));

#endif /* _FILTER_BYTECODE_H */
