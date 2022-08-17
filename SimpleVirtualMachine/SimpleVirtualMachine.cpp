#include "SimpleVirtualMachine.h"
#include "FileIO.h"

#include <iostream>
#include <sstream>
#include <vector>

namespace SVM
{
	void SimpleVirtualMachine::Init(const std::string& svmpath)
	{
		memset(m_Registers, 0, REGISTER_COUNT * sizeof(uint32_t));
		memset(m_Stack, 0, STACK_SIZE * sizeof(uint32_t));
		memset(m_Program, 0, PROGRAM_SIZE * sizeof(uint32_t));

		m_Registers[SVIP] = 0;
		m_Registers[SVSP] = -1;

		Decode(FileIO::ReadFileContent(svmpath));

		m_Running = true;
	}

	void SimpleVirtualMachine::Emulate()
	{
		while (m_Running)
		{
			uint32_t instr = Fetch();
			Execute(instr);
			m_Registers[SVIP]++;
		}
	}

	uint32_t SimpleVirtualMachine::Fetch() const
	{
		return m_Program[m_Registers[SVIP]];
	}

	void SimpleVirtualMachine::Decode(const std::string& data)
	{
		std::stringstream ss(data);
		std::string instruction;
		std::vector<std::string> instructions;

		while (std::getline(ss, instruction, '\n'))
		{
			if (instruction[0] == '\n' || instruction.length() == 0)
				continue;
			instructions.push_back(instruction);
		}

		for (const auto& instr : instructions)
			DecodeInstruction(instr);
	}

	void SimpleVirtualMachine::DecodeInstruction(const std::string& instr)
	{
		std::stringstream ss(instr);
		std::string op;
		
		static int i = 0;
		while (std::getline(ss, op, ' '))
		{
			m_Program[i] = DecodeStrToInt(op);
			i++;
		}
	}

	uint32_t SimpleVirtualMachine::DecodeStrToInt(const std::string& op)
	{
		// Instructions
		if (op == "PUSH")
			return PUSH;
		if (op == "POP")
			return POP;

		if (op == "HLT")
			return HLT;
		if (op == "SET")
			return SET;
		if (op == "MOV")
			return MOV;

		if (op == "ADD")
			return ADD;
		if (op == "SUB")
			return SUB;
		if (op == "MUL")
			return MUL;
		if (op == "DIV")
			return DIV;

		// Registers
		if (op == "SVA")
			return SVA;
		if (op == "SVB")
			return SVB;
		if (op == "SVC")
			return SVC;
		if (op == "SVD")
			return SVD;
		if (op == "SVE")
			return SVE;
		if (op == "SVF")
			return SVF;
		if (op == "SVIP")
			return SVIP;
		if (op == "SVSP")
			return SVSP;
		
		// Numbers
		return atoi(op.c_str());
	}

	void SimpleVirtualMachine::Execute(uint32_t instr)
	{
		switch (instr)
		{
		case PUSH:
		{
			m_Registers[SVSP]++;
			m_Stack[m_Registers[SVSP]] = m_Program[++m_Registers[SVIP]];
			break;
		}
		case POP:
		{
			uint32_t pop = m_Stack[m_Registers[SVSP]--];
			printf("SVMDebug->POP(%d)\n", pop);
			break;
		}
		case HLT:
		{
			m_Running = false;
			break;
		}
		case SET:
		{
			uint32_t reg = m_Program[++m_Registers[SVIP]];
			uint32_t val = m_Program[++m_Registers[SVIP]];
			m_Registers[reg] = val;
			break;
		}
		case MOV:
		{
			uint32_t reg1 = m_Program[++m_Registers[SVIP]];
			uint32_t reg2 = m_Program[++m_Registers[SVIP]];
			m_Registers[reg1] = m_Registers[reg2];
			break;
		}
		case ADD:
		{
			uint32_t x = m_Stack[m_Registers[SVSP]--];
			uint32_t y = m_Stack[m_Registers[SVSP]--];
			uint32_t res = y + x;
			m_Stack[++m_Registers[SVSP]] = res;
			break;
		}
		case SUB:
		{
			uint32_t x = m_Stack[m_Registers[SVSP]--];
			uint32_t y = m_Stack[m_Registers[SVSP]--];
			uint32_t res = y - x;
			m_Stack[++m_Registers[SVSP]] = res;
			break;
		}
		case MUL:
		{
			uint32_t x = m_Stack[m_Registers[SVSP]--];
			uint32_t y = m_Stack[m_Registers[SVSP]--];
			uint32_t res = y * x;
			m_Stack[++m_Registers[SVSP]] = res;
			break;
		}
		case DIV:
		{
			uint32_t x = m_Stack[m_Registers[SVSP]--];
			uint32_t y = m_Stack[m_Registers[SVSP]--];
			uint32_t res = y / x;
			m_Stack[++m_Registers[SVSP]] = res;
			break;
		}
		default:
			break;
		}
	}
}
