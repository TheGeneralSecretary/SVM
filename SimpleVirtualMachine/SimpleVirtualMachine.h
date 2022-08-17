#pragma once

#include <stdint.h>
#include <string>

#define REGISTER_COUNT 8
#define STACK_SIZE 256
#define PROGRAM_SIZE 1024

namespace SVM
{
	enum InstructionSet : uint32_t
	{
		PUSH,
		POP,

		HLT,
		SET,
		MOV,

		ADD,
		SUB,
		MUL,
		DIV,
	};

	enum Registers : uint32_t
	{
		SVA, SVB, SVC, SVD, SVE, SVF, SVIP, SVSP,
	};

	class SimpleVirtualMachine
	{
	public:
		void Init(const std::string& svmpath);
		void Emulate();

	private:
		uint32_t Fetch() const;
		void Decode(const std::string& data);
		void DecodeInstruction(const std::string& instr);
		uint32_t DecodeStrToInt(const std::string& op);
		void Execute(uint32_t instr);

	private:
		bool m_Running;
		uint32_t m_Registers[REGISTER_COUNT];
		uint32_t m_Stack[STACK_SIZE];
		uint32_t m_Program[PROGRAM_SIZE];
	};
}
