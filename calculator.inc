/*
---------------------------------------

	PawnCalculator	
	@author: Ino
	@version: 1.0.0
	@release: 07/11/2016
	@build: 1	
	@download: github.com/Ino42O/PawnCalculator

---------------------------------------

	Functions list:

		* TryCalculate(compute[], &result, &bool:fail, failstring[], const len = sizeof(failstring));
 	


 	Changelog:

 		07-11-2016:
 			* Initial release

        

 	Available types:
 		* Addition 			(+)
		* Subtraction 		(−)
		* Multiplication 	(×)
		* Division 			(÷)

---------------------------------------
*/

#include <a_samp>


#define _INC_CALCULATOR

#include <a_samp>

static const FailMessage[][] = 
{
	"Invalid character",
	"Out of range"
};

static const Chars[] = 
{
	" ",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0", 
	"/", 
	"-", 
	"+", 
	"*" 
	//"(",
	//")" 
};

stock TryCalculate(compute[], &result, &bool:fail, failstring[], const len = sizeof(failstring))
{
	new 
		size,
		step,
		failreason,
		tmp 		[24],
		newsize,
		stringa 	[24],
		numbers 	[24],
		sign 		[24]
	;


	// Get size
	do
	{
		if (compute[step] != '\0') size++;
		else break;			
	}
	while(++step);

	// Check valid characters / numbers
	new checkstep;
	do 
	{
		new bool:temp = false;
		for(new i = 0; i < sizeof(Chars); i++)
		{
			if (compute[checkstep] == Chars[i])
			{
				temp = true;
				break;
			}
		}

		if (!temp)
		{
			fail = true; 
			failreason = 0;
			break;
		}
	}
	while(++checkstep < size);

	if (fail) return format(failstring, len, "%s", FailMessage[failreason]);


	// Remove empty spaces
	for (new h = 0; h < size; h++)
	{
		if(compute[h] != '\0' && compute[h] != Chars[0])
		{
			tmp[newsize] = compute[h];
			newsize++;
		}	
	}

	// Store numbers and signs in array
	for (new k = 0, nIndex = -1, sIndex = -1; k < newsize; k++)
	{
		if (tmp[k] != '-' && tmp[k] != '+' && tmp[k] != '*' && tmp[k] != '/') 
		{
			format(stringa, sizeof(stringa), "%s%c", stringa, tmp[k]);
		}
		else
		{
			numbers[++nIndex] = strval(stringa);
			stringa[0] = '\0';

			sign[++sIndex] = ( (tmp[k] == '/') ? 0xB : (tmp[k] == '-') ? 0xC : (tmp[k] == '+') ? 0xD : 0xE );
		}
		
		if (k == newsize - 1)
		{
			numbers[++nIndex] = strval(stringa);
			stringa[0] = '\0';
		}

		if (numbers[k] > (2^31-1))
		{
			fail = true; 
			failreason = 1;
			break;
		}
	}

	if (fail) return format(failstring, len, "%s", FailMessage[failreason]);


	// Return result
	for (new k = 0; k < newsize; k++)
	{
		if (k == 0)
		{
			result = numbers[k];
		}
		else
		{
			switch(sign[k - 1])
			{
				case 0xB:
				{
					result /= numbers[k];
				}
				case 0xC:
				{
					result -= numbers[k];
				}
				case 0xD:
				{
					result += numbers[k];
				}
				case 0xE:
				{
					result *= numbers[k];
				}
			}
		}
	}
	return 1;
}