#include "spimcore.h"


/* ALU */
/* 10 Points */
/*  ALU(…)
1.  Implement the operations on input parameters A and B according to ALUControl.
2.  Output the result (Z) to ALUresult.
3.  Assign Zero to 1 if the result is zero; otherwise, assign 0.
4.  The following table shows the operations of the ALU.  */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* 10 Points */
/* instruction_fetch(…)
1. Fetch the instruction addressed by PC from Mem and write it to instruction.
2. Return 1 if a halt condition occurs; otherwise, return 0. */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	return 0;
}


/* instruction partition */
/* 10 Points */
/*  instruction_partition(…)
1.  Partition instruction into several parts (op, r1, r2, r3, funct, offset, jsec).
2.  Read line 41 to 47 of spimcore.c for more information. */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
/*  instruction_decode(…)
1.  Decode the instruction using the opcode (op).
2.  Assign the values of the control signals to the variables in the structure 
    controls (See spimcore.h file).
	The meanings of the values of the control signals:
	For MemRead, MemWrite or RegWrite, the value 1 means that enabled, 0 means 
	that disabled, 2 means “don’t care”.
	For RegDst, Jump, Branch, MemtoReg or ALUSrc, the value 0 or 1 indicates 
	the selected path of the multiplexer; 2 means “don’t care”. 
3.  Return 1 if a halt condition occurs; otherwise, return 0.*/
int instruction_decode(unsigned op,struct_controls *controls)
{
	controls->RegDst=0;
	controls->Jump=0;
	controls->Branch=0;
	controls->MemRead=0;
	controls->MemtoReg=0;
	controls->ALUOp=0;
	controls->MemWrite=0;
	controls->ALUSrc=0;
	controls->RegWrite=0;
	
	switch (op) 
	{
		case 0: // add, and, or, slt, sltu, sub
			controls->RegDst = 1; // multiplexer path 1
			controls->ALUOp = 7; // R-type instruction
			controls->RegWrite = 1; // enabled
			break;
                
                case 8: // addi
                	controls->ALUSrc = 1; // multiplexer path 1
                	controls->RegWrite = 1; // enabled
                	break;
                
        	case 4: // beq
                	controls->Branch = 1; 
                	controls->ALUOp = 1; // subtraction
                	break;
                
        	case 15: // lui
                	controls->ALUOp = 6; // shift left_extended value by 16
                	controls->ALUSrc = 1; // multiplexer path 1
                	controls->RegWrite = 1; // enabled
                	break;
                
	        case 35: // lw
	                controls->MemRead = 1; // enabled
	                controls->MemtoReg = 1; // multiplexer path 1
	                controls->ALUSrc = 1; // multiplexer path 1
	                controls->RegWrite = 1; // enabled
	                break;
                
	        case 10: // slti
	                controls->ALUOp = 2; // set less than
	                controls->ALUSrc = 1; // multiplexer path 1
	                controls->RegWrite = 1;
	                break;
	                
	        case 11: // sltiu
	                controls->ALUOp = 3; // set less than unsigned
	                controls->ALUSrc = 1; // multiplexer path 1
	                controls->RegWrite = 1; // enabled
	                break;
	                
	        case 43: // sw
	                controls->RegDst = 2; // don’t care
	                controls->MemtoReg = 2; // don’t care
	                controls->MemWrite = 1; // enabled
	                controls->ALUSrc = 1; // multiplexer path 1
	                break;
	                
	        case 2: // j
	                controls->Jump = 1;
	                break;
	                
	                default: return 1; // If a halt condition occurs
	    } 
	    return 0; // If no halt condition occurs
}


/* Read Register */
/* 5 Points */
/*  read_register(…)
1.  Read the registers addressed by r1 and r2 from Reg, and write the read values 
    to data1 and data2 respectively. */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	//read r1 and r2 address from Reg, write to data1 and data2
	*data1 = Reg[r1];
        *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
/*  sign_extend(…)
1.  Assign the sign-extended value of offset to extended_value. */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
/*  ALU_operations(…)
1.  Apply ALU operations on data1, and data2 or extended_value (determined by ALUSrc).
2.  The operation performed is based on ALUOp and funct.
3.  Apply the function ALU(…).
4.  Output the result to ALUresult.
5.  Return 1 if a halt condition occurs; otherwise, return 0.  */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	return 0;

}

/* Read / Write Memory */
/* 10 Points */
/*  rw_memory(…)
1.  Base on the value of MemWrite or MemRead to determine memory write operation or memory read operation.
2.  Read the content of the memory location addressed by ALUresult to memdata.
3.  Write the value of data2 to the memory location addressed by ALUresult.
4.  Return 1 if a halt condition occurs; otherwise, return 0.  */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	// If MemRead or MemWrite is asserted and word not aligned or out of bounds, halt
	if ((MemRead | MemWrite) && (ALUresult % 4 != 0 | (ALUresult >> 2) > 0xFFFF))  
	{
		// Return 1 if a halt condition occurs
		return 1;
        }
        
        if (MemRead)
        {
        	// Read the content of the memory location addressed by ALUresult to memdata
        	*memdata = Mem[ALUresult >> 2];
        }
        
            if (MemWrite)
            {
            	// Write the value of data2 to the memory location addressed by ALUresult
                Mem[ALUresult >> 2] = data2;
            }
            
            // Return 0 if no halt condition occurs
            return 0;
}


/* Write Register */
/* 10 Points */
/*  write_register(…)
1.  Write the data (ALUresult or memdata) to a register (Reg) addressed by r2 or r3. */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
/*  PC_update(…)
1.  Update the program counter (PC).  */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
